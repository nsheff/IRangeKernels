#PACKAGE DOCUMENTATION
#' IRangeKernels - Kernel density estimation using IRanges
#'
#' The package extends IRanges to allow fast sliding window density estimation 
#' by implementing a Views kernel multiplication function, viewMuls, 
#' to multiply Views by a vector.
#'
#' @references This has not been published, see 
#' \url{github.com/sheffien}
#' @import IRanges
#' @docType package
#' @useDynLib IRangeKernels
#' @name IRangeKernels
#' @author Nathan Sheffield
NULL




#FUNCTION DOCUMENTATION
#' viewMuls
#'
#' Analogous to the IRanges viewSums, but multiplies by a vector; so you can think
#' of it as a weighted sum, or a kernel density estimate.
#'
#' @param x 		Views object.
#' @param na.rm	remove NAs?
#' @param y 		kernel vector or weights to multiply by; should be a vector matching the length of x.
#' @export
setGeneric("viewMuls", signature="x",
           function(x, na.rm = FALSE, y) standardGeneric("viewMuls"))


setMethod("viewMuls", "RleViews",
          function(x, na.rm = FALSE, y)
          .Call2("RleViews_viewMuls", trim(x), na.rm, y, PACKAGE="IRangeKernels"))


