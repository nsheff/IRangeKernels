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


/*
"The author of packB is responsible for ensuring that p_myCfun has an appropriate declaration. In the future R may provide some automated tools to simplify exporting larger numbers of routines."

These are declarations for the callable functions retrieved from IRanges.
//based on function headings defined in IRanges_interface.h
*/


//cachedIRanges (*p_cache_IRanges)(SEXP);
//int (*p_get_cachedIRanges_length)(const cachedIRanges *);
//int (*p_get_cachedIRanges_elt_width)(const cachedIRanges *, int);
//int (*p_get_cachedIRanges_elt_start)(const cachedIRanges *, int);
//SEXP (*p_get_IRanges_names)(SEXP);

//Updating for version 1.22
IRanges_holder (*p_hold_IRanges)(SEXP x);
int (*p_get_length_from_IRanges_holder)(const IRanges_holder *);
int (*p_get_width_elt_from_IRanges_holder)(const IRanges_holder *, int);
int (*p_get_start_elt_from_IRanges_holder)(const IRanges_holder *, int);
SEXP (*p_get_IRanges_names)(SEXP);

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


