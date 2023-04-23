#include "preproc.h"

const char* preproc_keyword_names[] = {
	"#def",
	"#isdef",
	"#undef",
	"#ldef",
	"#lisdef",
	"#lundef",
	"#import",
	"#include",
	"#eval",
	"#if",
	"#concat",
	"#substr",
	"#compare",
	"#len",
	"#drop",
	"#nip",
	"#dup",
	"#over",
	"#tuck",
	"#swap",
	"#rot",
	"#2drop",
	"#2nip",
	"#2dup",
	"#2over",
	"#2tuck",
	"#2swap",
	"#2rot",
	"#+",
	"#-",
	"#*",
	"#/",
	"#%",
	"#u/",
	"#u%",
	"#=",
	"#!=",
	"#<",
	"#<=",
	"#>",
	"#>=",
	"#u<",
	"#u<=",
	"#u>",
	"#u>=",
	"#f+",
	"#f-",
	"#f*",
	"#f/",
	"#f%",
	"#f<",
	"#f<=",
	"#f>",
	"#f>=",
	"#&",
	"#|",
	"#^",
	"#~",
	"#<<",
	"#>>",
	"#ftoi",
	"#itof",
	"#fmti",
	"#fmtu",
	"#fmtf"
};

size_t preproc_keyword_names_len = sizeof(preproc_keyword_names) / sizeof(char*);
