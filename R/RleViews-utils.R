
setGeneric("viewMuls", signature="x",
           function(x, na.rm = FALSE, y) standardGeneric("viewMuls"))


setMethod("viewMuls", "RleViews",
          function(x, na.rm = FALSE, y)
          .Call2("RleViews_viewMuls", trim(x), na.rm, y, PACKAGE="IRangesMultiplication"))


