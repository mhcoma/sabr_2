#include "interpreter.h"
#include "interpreter_op.h"

extern inline sabr_value_t* sabr_memory_pool_top(sabr_memory_pool_t* pool);

bool sabr_interpreter_init(sabr_interpreter_t* inter) {
    deque_init(sabr_value_t, &inter->data_stack);
    deque_init(sabr_value_t, &inter->switch_stack);

    deque_init(sabr_for_data_t, &inter->for_data_stack);
    deque_init(sabr_cs_data_t, &inter->call_stack);

    rbt_init(sabr_def_data_t, &inter->global_words);
    deque_init(cctl_ptr(rbt(sabr_def_data_t)), &inter->local_words_stack);

    vector_init(cctl_ptr(vector(sabr_value_t)), &inter->struct_vector);

    deque_init(size_t, &inter->local_memory_size_stack);

    return true;
}

bool sabr_interpreter_del(sabr_interpreter_t* inter) {
    deque_free(sabr_value_t, &inter->data_stack);
    deque_free(sabr_value_t, &inter->switch_stack);

    deque_free(sabr_for_data_t, &inter->for_data_stack);
    deque_free(sabr_cs_data_t, &inter->call_stack);

    rbt_free(sabr_def_data_t, &inter->global_words);
    for (size_t i = 0; i < inter->local_words_stack.size; i++)
        rbt_free(sabr_def_data_t, *deque_at(cctl_ptr(rbt(sabr_def_data_t)), &inter->local_words_stack, i));
    deque_free(cctl_ptr(rbt(sabr_def_data_t)), &inter->local_words_stack);

    for (size_t i = 0; i < inter->struct_vector.size; i++)
        vector_free(sabr_value_t, *vector_at(cctl_ptr(vector(sabr_value_t)), &inter->struct_vector, i));
    vector_free(cctl_ptr(vector(sabr_value_t)), &inter->struct_vector);

    deque_free(size_t, &inter->local_memory_size_stack);
	sabr_memory_pool_del(&inter->memory_pool);
	sabr_memory_pool_del(&inter->global_memory_pool);

    return true;
}

sabr_bytecode_t* sabr_interpreter_load_bytecode(sabr_interpreter_t* inter, const char* filename) {
	FILE* file;
	size_t size;

#if defined(_WIN32)
	wchar_t filename_windows[PATH_MAX] = {0, };
	if (!sabr_convert_string_mbr2c16(filename, filename_windows, &(inter->convert_state))) {
		fputs(sabr_errmsg_open, stderr);
		return NULL;
	}
	if (_waccess(filename_windows, R_OK)) {
		fputs(sabr_errmsg_open, stderr);
		return NULL;
	}
	file = _wfopen(filename_windows, L"rb");
#else
	if (access(filename, R_OK)) {
		fputs(sabr_errmsg_open, stderr);
		return NULL;
	}
	file = fopen(filename, "rb");
#endif

	if (!file) {
		fputs(sabr_errmsg_open, stderr);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	uint8_t* code = (uint8_t*) malloc(size);
	if (!code) {
		fclose(file);
		fputs(sabr_errmsg_alloc, stderr);
		return NULL;
	}

	int a = fread(code, size, 1, file);
	fclose(file);

	if (a != 1) {
		free(code);
		fputs(sabr_errmsg_read, stderr);
		return NULL;
	}

	sabr_bytecode_t* bc = (sabr_bytecode_t*) malloc(sizeof(sabr_bytecode_t));
	if (!bc) {
		free(code);
		fputs(sabr_errmsg_alloc, stderr);
		return NULL;
	}
	sabr_bytecode_init(bc);

	size_t index = 0;
	while (index < size) {
		sabr_bcop_t bcop;
		bcop.oc = code[index++];
		if (sabr_opcode_has_operand(bcop.oc)) {
			for (size_t i = 0; i < 8; i++) bcop.operand.bytes[i] = code[index++];
			sabr_bytecode_write_bcop_with_value(bc, bcop.oc, bcop.operand);
		}
		else sabr_bytecode_write_bcop(bc, bcop.oc);
	}

	return bc;
}

bool sabr_interpreter_run_bytecode(sabr_interpreter_t* inter, sabr_bytecode_t* bc) {
	for (size_t index = 0; index < bc->bcop_vec.size; index++) {
		sabr_bcop_t bcop = *vector_at(sabr_bcop_t, &bc->bcop_vec, index);
		uint32_t result = interpreter_op_functions[bcop.oc - 1](inter, bcop, &index);
	}
	return true;
}

bool sabr_interpreter_memory_pool_init(sabr_interpreter_t* inter, size_t size, size_t global_size) {
	if (!sabr_memory_pool_init(&inter->memory_pool, size)) return false;
	if (!sabr_memory_pool_init(&inter->global_memory_pool, global_size)) return false;
	return true;
}

bool sabr_memory_pool_init(sabr_memory_pool_t* pool, size_t size) {
	pool->data = (sabr_value_t*) malloc(sizeof(size_t) * size);
	pool->size = size;
	pool->index = 0;
	if (pool->data) return true;
	return false;
}

void sabr_memory_pool_del(sabr_memory_pool_t* pool) {
	free(pool->data);
	pool->data = NULL;
}

bool sabr_memory_pool_alloc(sabr_memory_pool_t* pool, size_t size) {
	if (pool->index + size >= pool->size) return false;
	pool->index += size;
	return true;
}

bool sabr_memory_pool_free(sabr_memory_pool_t* pool, size_t size) {
	if (pool->index - size < pool->index) return false;
	pool->index -= size;
	return true;
}

bool sabr_interpreter_pop(sabr_interpreter_t* inter, sabr_value_t* v) {
	if (!inter->data_stack.size) {
		fputs(sabr_errmsg_stackunderflow, stderr);
		return false;
	}
	*v = *deque_back(sabr_value_t, &inter->data_stack);
	deque_pop_back(sabr_value_t, &inter->data_stack);
	return true;
}

bool sabr_interpreter_push(sabr_interpreter_t* inter, sabr_value_t v) {
	if (!deque_push_back(sabr_value_t, &inter->data_stack, v)) {
		fputs(sabr_errmsg_alloc, stderr);
		return false;
	}
	return true;
}