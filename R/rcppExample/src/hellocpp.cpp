// After any C++ interface changes, the function compileAttributes() must be run
// This dynamically generates the RcppExports.cpp file
// Otherwise expect error about function not callable

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
RcppExport SEXP helloWorldCpp(SEXP name) // SEXP is the R type
{
  // as goes R -> C++ (template to specify type for coercion)
  std::string strName = Rcpp::as<std::string>(name);
  std::string hello = "Hello, ";
  std::string helloPrompt = hello + strName;
  // wrap goes C++ object -> R object
  return Rcpp::wrap(helloPrompt);
}