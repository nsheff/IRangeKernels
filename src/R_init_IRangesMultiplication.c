#include "IRangesMultiplication.h"
#include "IRanges_interface.h"
#include "IRanges_defines.h"
#include <R_ext/Rdynload.h>

#define CALLMETHOD_DEF(fun, numArgs) {#fun, (DL_FUNC) &fun, numArgs}

#define REGISTER_CCALLABLE(fun) \
	R_RegisterCCallable("IRanges", #fun, (DL_FUNC) &fun)

static const R_CallMethodDef callMethods[] = {

/* RleViews_utils.c */
	CALLMETHOD_DEF(RleViews_viewMuls, 3)

/* XIntegerViews_utils.c */
	/*CALLMETHOD_DEF(XIntegerViews_summaryN, 3),*/

};



void R_init_IRangesMultiplication(DllInfo *info)
{

/* _get_IRanges_length = R_GetCCallable("IRanges", "_get_IRanges_length");*/
 	p_cache_IRanges = ( cachedIRanges(*)(SEXP) ) R_GetCCallable("IRanges", "_cache_IRanges");
	p_get_cachedIRanges_length = (int(*)(const cachedIRanges *)) R_GetCCallable("IRanges", "_get_cachedIRanges_length");

	p_get_cachedIRanges_elt_start = (int(*)(const cachedIRanges *, int)) R_GetCCallable("IRanges", "_get_cachedIRanges_elt_start");
	p_get_cachedIRanges_elt_width = (int(*)(const cachedIRanges *, int)) R_GetCCallable("IRanges", "_get_cachedIRanges_elt_width");
	p_get_IRanges_names = (SEXP(*)(SEXP)) R_GetCCallable("IRanges", "_get_IRanges_names");

}

