helloWorldCpp <- function(name) {
  return(
    .Call(  # mechanism to call C++ function. Function must be preceeded by "// [[Rcpp::export]]"
      "helloWorldCpp",  # first argument is name of C++ function
      name,  # next are arguments to C++ function (passed as SEXP types)
      PACKAGE = "rcppExample"  # last is name of package C++ function is exported from
    )
  )
}