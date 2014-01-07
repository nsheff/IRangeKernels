#include "IRanges_defines.h"
#include <string.h>

#define DEBUG_IRANGES 1

#define INIT_STATIC_SYMBOL(NAME) \
{ \
	if (NAME ## _symbol == NULL) \
		NAME ## _symbol = install(# NAME); \
}


SEXP RleViews_viewMuls(
	SEXP x,
	SEXP na_rm,
	SEXP y
);

/*SEXP XIntegerViews_summaryN(
	SEXP x,
	SEXP na_rm,
	SEXP y
);*/


cachedIRanges(*p_cache_IRanges)(SEXP);
int(*p_get_cachedIRanges_length)(const cachedIRanges *);
int(*p_get_cachedIRanges_elt_width)(const cachedIRanges *, int);
int(*p_get_cachedIRanges_elt_start)(const cachedIRanges *, int);
SEXP(*p_get_IRanges_names)(SEXP);


/*
SEXP _get_IRanges_names(SEXP x);
int _get_cachedIRanges_elt_width(
	const cachedIRanges *cached_x,
	int i
);

int _get_cachedIRanges_elt_start(
	const cachedIRanges *cached_x,
	int i
);*/
