#include "../stdafx.h"

#include "ExportPythonSDK.h"

#include "Field.h"
#include "RecordCreator.h"
#include "RecordInfo.h"

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

	class_<SRC::RecordData>("record_ref", no_init);

	class_<RecordCreator, boost::shared_ptr<RecordCreator>>("RecordCreator", no_init)
		.def(
			"finalize_record", &RecordCreator::FinalizeRecord
			, "Returns the RecordRef that contains the data for the record."
		)
		.add_property(
			"var_data_size", &RecordCreator::GetVarDataSize
			, "The number of bytes of variable-length data in this record."
		)
		.def(
			"reset", &RecordCreator::Reset
			, arg("var_data_size")=0
			, "Sets the capacity in bytes for variable-length data in this record to `var_data_size`."
		)
	;

	class_<Field>("field", no_init)
		.add_property("size", &Field::Size, "The size of the field in bytes.")
		.add_property("type", &Field::Type, "The type of the field.")
		.add_property("scale", &Field::Scale, "The scale of the field.")
		.add_property("name", &Field::Name, "The name of the field.")
		.add_property("position", &Field::Position, "The 0-based index of the field in its parent RecordInfo.")
		.add_property("source", &Field::Source, "The source of the field.")
		.add_property("description", &Field::Description, "The description of the field.")
		.def(
			"get_as_bool", &Field::GetAsBool
			, arg("record")
			, "Returns the value of this field in the specified `record` as a boolean value."
		)
		.def(
			"set_from_bool", &Field::SetFromBool
			, (arg("record_creator"), arg("value"))
			, "Sets the value of this field in the specified `record_creator` from a boolean `value`."
		)
		.def(
			"get_as_int32", &Field::GetAsInt32
			, arg("record")
			, "Returns the value of this field in the specified `record` as an int32 value."
		)
		.def(
			"set_from_int32", &Field::SetFromInt32
			, (arg("record_creator"), arg("value"))
			, "Sets the value of this field in the specified `record_creator` from an int32 `value`."
		)
		.def(
			"get_as_int64", &Field::GetAsInt64
			, arg("record")
			, "Returns the value of this field in the specified `record` as an int64 value."
		)
		.def(
			"set_from_int64", &Field::SetFromInt64
			, (arg("record_creator"), arg("value"))
			, "Sets the value of this field in the specified `record_creator` from an int64 `value`."
		)
		.def(
			"get_as_double", &Field::GetAsDouble
			, arg("record")
			, "Returns the value of this field in the specified `record` as a double value."
		)
		.def(
			"set_from_double", &Field::SetFromDouble
			, (arg("record_creator"), arg("value"))
			, "Sets the value of this field in the specified `record_creator` from a double `value`."
		)
		.def(
			"get_as_string", &Field::GetAsString
			, arg("record")
			, "Returns the value of this field in the specified `record` as a string value."
		)
		.def(
			"set_from_string", &Field::SetFromString
			, (arg("record_creator"), arg("value"))
			, "Sets the value of this field in the specified `record_creator` from a string `value`."
		)
		.def(
			"get_null", &Field::GetNull
			, arg("record")
			, "Returns true if the value of this field in the specified `record` is [Null]."
		)
		.def(
			"set_null", &Field::SetNull
			, arg("record_creator")
			, "Sets the value of this field in the specified `record_creator` to [Null]."
		)
	;

	class_<RecordInfo, boost::shared_ptr<RecordInfo>>("record_info")
		.def("__len__", &RecordInfo::NumFields)
		.def("num_fields", &RecordInfo::NumFields)
		.def("__getitem__", &RecordInfo::At)
		.def("at", &RecordInfo::At)
		.def("add_field_from_xml", &RecordInfo::AddFieldFromXml)
		.def("add_field", &RecordInfo::AddField)
		.def("get_record_xml_meta_data", &RecordInfo::GetRecordXmlMetaData)
		.def("init_from_xml", &RecordInfo::InitFromXml)
		.def("construct_record_creator", &RecordInfo::ConstructRecordCreator)
		.def("get_field_num", &RecordInfo::GetFieldNum)
		.def("get_field_by_name", &RecordInfo::GetFieldByName);

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
