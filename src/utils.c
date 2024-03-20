#include "utils.h"

#if defined (_WIN32)
	bool sabr_convert_string_mbr2c16(const char* src, wchar_t* dest, mbstate_t* convert_state) {
		const char* end = src + strlen(src);

		while (true) {
			char16_t out;
			size_t rc = mbrtoc16(&out, src, end - src + 1, convert_state);
			if (!rc) return true;
			if (rc == (size_t) -3) dest++;
			if (rc > (size_t) -3) return false;

			src += rc; *(dest++) = out;
		}
	}
#endif

#if defined (_WIN32)
	bool sabr_get_full_path(const char* src_mbr, char* dest_mbr, wchar_t* dest_utf16, mbstate_t* convert_state)
#else
	bool sabr_get_full_path(const char* src, char* dest)
#endif
{
#if defined(_WIN32)
	wchar_t src_utf16[PATH_MAX] = {0, };

	if (!sabr_convert_string_mbr2c16(src_mbr, src_utf16, convert_state)) return false;
	if (!_wfullpath(dest_utf16, src_utf16, PATH_MAX)) return false;
	if (!_fullpath(dest_mbr, src_mbr, PATH_MAX)) return false;
#else
	if (!realpath(src, dest)) return false;
#endif
	return true;
}