#include "ExportPythonSDK.h"

#pragma warning( push, 0 )
#define BOOST_PYTHON_STATIC_LIB
#include <boost\python\def.hpp>
#include <boost\python\extract.hpp>
#include <boost\python\module.hpp>
#include <boost\python\str.hpp>
#include <boost\python.hpp>
#include <boost\python\exception_translator.hpp>
#include <boost\exception\diagnostic_information.hpp>
#include <boost\shared_ptr.hpp>
#pragma warning( pop )

#include <iostream>

using std::exception;
using std::cout;
using std::cerr;
using std::wcerr;

char const* yay()
{
  return "Yay!";
}

class foo
{
public:
	int
	int_method();

	boost::python::str
	str_method();

	void
	print_method(boost::python::str name);
};

BOOST_PYTHON_MODULE(Python_AlteryxYXDB)
{
	using namespace boost::python;
	def("yay", yay);

	boost::python::class_<foo, boost::shared_ptr<foo>>("foo")
		.def("int_method", &foo::int_method)
		.def("str_method", &foo::str_method)
		.def("print_method", &foo::print_method);
}

int
foo::int_method()
{
	return 0;
}

boost::python::str
foo::str_method()
{
	return "a";
}

void
foo::print_method(boost::python::str name)
{
	cout << "Hello, " << std::string{boost::python::extract<std::string>(name)} << "!\n";
}
