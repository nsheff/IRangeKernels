#include "IRangesMultiplication.h"
#include <R_ext/Arith.h>
#include <R_ext/Utils.h>
#include <limits.h>

#define R_INT_MIN	(1+INT_MIN)



/*
 * --- .Call ENTRY POINT ---
 */
//Nathan's new function
SEXP RleViews_viewMuls(SEXP x, SEXP na_rm, SEXP y)
{
	char type = '?';
	int i, start, width, ans_length, index,
	    lower_run, upper_run, lower_bound, upper_bound;
	int max_index, *lengths_elt;
	SEXP ans, subject, values, lengths, ranges, names;
	IRanges_holder cached_ranges;
	double *y_c = REAL(y);
	int kernelIndex, count, multiCounter;
	int * intValues;
	double* realAns;
	subject = GET_SLOT(x, install("subject"));
	values = GET_SLOT(subject, install("values"));
	lengths = GET_SLOT(subject, install("lengths"));
	ranges = GET_SLOT(x, install("ranges"));
	cached_ranges = p_cache_IRanges(ranges);
	ans_length = p_get_cachedIRanges_length(&cached_ranges);

	ans = R_NilValue;
	switch (TYPEOF(values)) {
    case LGLSXP:
    case INTSXP:
		type = 'r';
		PROTECT(ans = NEW_NUMERIC(ans_length));
		realAns = REAL(ans);
		intValues = INTEGER(values);
		break;
    case REALSXP:
		type = 'r';
		PROTECT(ans = NEW_NUMERIC(ans_length));
		break;
    case CPLXSXP:
		type = 'c';
		PROTECT(ans = NEW_COMPLEX(ans_length));
		break;
    default:
		error("Rle must contain either 'integer', 'numeric', or 'complex' values");
    }

	if (!IS_LOGICAL(na_rm) || LENGTH(na_rm) != 1 || LOGICAL(na_rm)[0] == NA_LOGICAL)
		error("'na.rm' must be TRUE or FALSE");

	lengths_elt = INTEGER(lengths);
	max_index = LENGTH(lengths) - 1;
	index = 0;
	upper_run = *lengths_elt;
	for (i = 0; i < ans_length; i++) {
		if (i % 100000 == 99999)
			R_CheckUserInterrupt();
		start = p_get_cachedIRanges_elt_start(&cached_ranges, i);
		width = p_get_cachedIRanges_elt_width(&cached_ranges, i);
		if (type == 'i') {
			INTEGER(ans)[i] = 0;
		} else if (type == 'r') {
			REAL(ans)[i] = 0;
		} else if (type == 'c') {
			COMPLEX(ans)[i].r = 0;
			COMPLEX(ans)[i].i = 0;
		}
		if (width > 0) {
			while (index > 0 && upper_run > start) {
				upper_run -= *lengths_elt;
				lengths_elt--;
				index--;
			}
			while (upper_run < start) {
				lengths_elt++;
				index++;
				upper_run += *lengths_elt;
			}
			lower_run = upper_run - *lengths_elt + 1;
			lower_bound = start;
			upper_bound = start + width - 1;
			if (type == 'i') {
				while (lower_run <= upper_bound) {
					if (INTEGER(values)[index] == NA_INTEGER) {
						if (!LOGICAL(na_rm)[0]) {
							INTEGER(ans)[i] = NA_INTEGER;
							break;
						}
					} else {
						INTEGER(ans)[i] += INTEGER(values)[index] *
						    (1 + (upper_bound < upper_run ? upper_bound : upper_run) -
						         (lower_bound > lower_run ? lower_bound : lower_run));
					}
					if (index < max_index) {
						lengths_elt++;
						index++;
						lower_run = upper_run + 1;
						lower_bound = lower_run;
						upper_run += *lengths_elt;
					} else {
						break;
					}
				}
				if (INTEGER(ans)[i] != NA_INTEGER &&
					(INTEGER(ans)[i] > INT_MAX || INTEGER(ans)[i] < R_INT_MIN))
					error("Integer overflow");
			} else if (type == 'r') {
				kernelIndex = 0;
				while (lower_run <= upper_bound) {
					/*if (ISNAN(INTEGER(values)[index])) {
						if (!LOGICAL(na_rm)[0]) {
							REAL(ans)[i] = NA_REAL;
							break;
						}
					} else */{
						//if values is zero, we do nothing.
	count = (1 + (upper_bound < upper_run ? upper_bound : upper_run) -
						         (lower_bound > lower_run ? lower_bound : lower_run));
					//	printf("index: %d, values: %d, y: %f, count: %d, lower_run: %d, upper_run:%d, lower_bound: %d, upper_bound:%d, kernelIndex:%d\n", index, INTEGER(values)[index], REAL(y)[kernelIndex], count, lower_run, upper_run, lower_bound, upper_bound, kernelIndex);
	multiCounter = 0;
						if (intValues[index] > 0) {
							while( multiCounter < count ) {
								REAL(ans)[i] += intValues[index] * y_c[kernelIndex];
								multiCounter++;
								kernelIndex++;
							}
						} else {
kernelIndex += count;
	}
						//otherwise, multiply that value by the correct kernel weight and sum
						//looping through weights.

					//	REAL(ans)[i] += INTEGER(values)[index] * REAL(y)[index] *
					//	    (1 + (upper_bound < upper_run ? upper_bound : upper_run) -
					//	         (lower_bound > lower_run ? lower_bound : lower_run));
					}
					if (index < max_index) {
						lengths_elt++;
						index++;
						lower_run = upper_run + 1;
						lower_bound = lower_run;
						upper_run += *lengths_elt;
					} else {
						break;
					}
				}
			} else if (type == 'c') {
				while (lower_run <= upper_bound) {
					if (ISNAN(COMPLEX(values)[index].r) || ISNAN(COMPLEX(values)[index].i)) {
						if (!LOGICAL(na_rm)[0]) {
							COMPLEX(ans)[i].r = NA_REAL;
							COMPLEX(ans)[i].i = NA_REAL;
							break;
						}
					} else {
						COMPLEX(ans)[i].r += COMPLEX(values)[index].r *
						    (1 + (upper_bound < upper_run ? upper_bound : upper_run) -
						         (lower_bound > lower_run ? lower_bound : lower_run));
						COMPLEX(ans)[i].i += COMPLEX(values)[index].i *
						    (1 + (upper_bound < upper_run ? upper_bound : upper_run) -
						         (lower_bound > lower_run ? lower_bound : lower_run));
					}
					if (index < max_index) {
						lengths_elt++;
						index++;
						lower_run = upper_run + 1;
						lower_bound = lower_run;
						upper_run += *lengths_elt;
					} else {
						break;
					}
				}
			}
		}
	}
	PROTECT(names = duplicate(p_get_IRanges_names(ranges)));
	SET_NAMES(ans, names);
	UNPROTECT(2);
	return ans;
}



