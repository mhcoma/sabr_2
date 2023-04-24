#ifndef __PREPROC_H__
#define __PREPROC_H__

#include "stdint.h"
#include "stddef.h"

typedef enum preproc_keyword_enum {
	PREPROC_FUNC,
	PREPROC_MACRO,
	PREPROC_ISDEF,
	PREPROC_UNDEF,
	PREPROC_GETDEF,
	PREPROC_LFUNC,
	PREPROC_LMACRO,
	PREPROC_LISDEF,
	PREPROC_LUNDEF,
	PREPROC_LGETDEF,
	PREPROC_IMPORT,
	PREPROC_INCLUDE,
	PREPROC_EVAL,
	PREPROC_IF,
	PREPROC_CONCAT,
	PREPROC_SUBSTR,
	PREPROC_COMPARE,
	PREPROC_LEN,
	PREPROC_DROP,
	PREPROC_NIP,
	PREPROC_DUP,
	PREPROC_OVER,
	PREPROC_TUCK,
	PREPROC_SWAP,
	PREPROC_ROT,
	PREPROC_2DROP,
	PREPROC_2NIP,
	PREPROC_2DUP,
	PREPROC_2OVER,
	PREPROC_2TUCK,
	PREPROC_2SWAP,
	PREPROC_2ROT,
	PREPROC_ADD,
	PREPROC_SUB,
	PREPROC_MUL,
	PREPROC_DIV,
	PREPROC_MOD,
	PREPROC_UDIV,
	PREPROC_UMOD,
	PREPROC_EQU,
	PREPROC_NEQ,
	PREPROC_GRT,
	PREPROC_GEQ,
	PREPROC_LST,
	PREPROC_LEQ,
	PREPROC_UGRT,
	PREPROC_UGEQ,
	PREPROC_ULST,
	PREPROC_ULEQ,
	PREPROC_FADD,
	PREPROC_FSUB,
	PREPROC_FMUL,
	PREPROC_FDIV,
	PREPROC_FMOD,
	PREPROC_FGRT,
	PREPROC_FGEQ,
	PREPROC_FLST,
	PREPROC_FLEQ,
	PREPROC_AND,
	PREPROC_OR,
	PREPROC_XOR,
	PREPROC_NOT,
	PREPROC_LSFT,
	PREPROC_RSFT,
	PREPROC_FTOI,
	PREPROC_ITOF,
	PREPROC_FMTI,
	PREPROC_FMTU,
	PREPROC_FMTF
} preproc_keyword;

extern const char* preproc_keyword_names[];
extern size_t preproc_keyword_names_len;

#endif