#include "IRangesMultiplication.h"
#include "IRanges_interface.h"
#include "IRanges_defines.h"
#include <R_ext/Rdynload.h>

//define some macros to make registering functions easier
#define CALLMETHOD_DEF(fun, numArgs) {#fun, (DL_FUNC) &fun, numArgs}

#define REGISTER_CCALLABLE(fun) \
	R_RegisterCCallable("IRanges", #fun, (DL_FUNC) &fun)


//registration information: 
//Each routine in the registration information is specified by giving a name along with the address of the routine and any information about the number and type of the parameters.
static const R_CallMethodDef callMethods[] = {

/* RleViews_utils.c */
	CALLMETHOD_DEF(RleViews_viewMuls, 3)

/* XIntegerViews_utils.c */
	/*CALLMETHOD_DEF(XIntegerViews_summaryN, 3),*/

};


//Init function for this package,
// get (retrieve) callable functions from the IRanges package
// using R_GetCCallable (http://cran.r-project.org/doc/manuals/r-release/R-exts.html#Registering-native-routines)
// get pointers to functions with name p_functioName
//these are roginally efined in IRanges_interface.h

void R_init_IRangesMultiplication(DllInfo *info)
{

/* _get_IRanges_length = R_GetCCallable("IRanges", "_get_IRanges_length");*/
 	p_cache_IRanges = ( IRanges_holder(*)(SEXP) ) R_GetCCallable("IRanges", "_hold_IRanges");
	p_get_cachedIRanges_length = (int(*)(const IRanges_holder *)) R_GetCCallable("IRanges", "_get_length_from_IRanges_holder");

	p_get_cachedIRanges_elt_start = (int(*)(const IRanges_holder *, int)) R_GetCCallable("IRanges", "_get_start_elt_from_IRanges_holder");
	p_get_cachedIRanges_elt_width = (int(*)(const IRanges_holder *, int)) R_GetCCallable("IRanges", "_get_width_elt_from_IRanges_holder");
	p_get_IRanges_names = (SEXP(*)(SEXP)) R_GetCCallable("IRanges", "_get_IRanges_names");

}




