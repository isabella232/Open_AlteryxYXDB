#include "../stdafx.h"

#include <vector>

#pragma warning( push, 0 )
#define BOOST_PYTHON_STATIC_LIB

#include <boost\python\def.hpp>
#include <boost\python\extract.hpp>
#include <boost\python\module.hpp>
#include <boost\python\list.hpp>
#include <boost\python\str.hpp>
#include <boost\python.hpp>
#include <boost\python\exception_translator.hpp>
#include <boost\exception\diagnostic_information.hpp>
#include <boost\shared_ptr.hpp>
#pragma warning( pop )



#include "../Open_AlteryxYXDB.h"

#include "ExportPythonSDK.h"

#include "Field.h"
#include "RecordCreator.h"
#include "RecordInfo.h"
#include "RecordRef.h"
#include "Python.h"





#include <iostream>

using std::exception;
using std::cout;
using std::cerr;
using std::wcerr;

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

struct AlteryxYXDB
{
	Alteryx::OpenYXDB::Open_AlteryxYXDB m_alteryxYXDB;
	std::vector<SRC::E_FieldType> m_typeVector;

	void create(boost::python::str filename, boost::python::str xml) {
		const char *const utf8_filename = boost::python::extract<const char *const>(filename);
		const char *const utf8_xml = boost::python::extract<const char *const>(xml);

		m_alteryxYXDB.Create(SRC::ConvertToWString(utf8_filename), SRC::ConvertToWString(utf8_xml));
	}

	void append(SRC::RecordData *record_data) {
		m_alteryxYXDB.AppendRecord(record_data);
	}

	void open(boost::python::str filename) {
		const char *const utf8_filename = boost::python::extract<const char *const>(filename);
		m_alteryxYXDB.Open(SRC::ConvertToWString(utf8_filename));
		unsigned numFields = m_alteryxYXDB.m_recordInfo.NumFields();
		m_typeVector.reserve(numFields);
		for (unsigned i = 0; i < numFields; ++i)
		{
			m_typeVector.push_back(m_alteryxYXDB.m_recordInfo[i]->m_ft);
		}



	}

	boost::python::list readRow()
	{
		boost::python::list retList;

		const SRC::RecordData* rec = m_alteryxYXDB.ReadRecord();
		if (rec)
		{

			unsigned numFields = m_alteryxYXDB.m_recordInfo.NumFields();
			for (unsigned i = 0; i < numFields; ++i)
			{
				switch (m_typeVector[i])
				{
				case SRC::E_FieldType::E_FT_Bool:
					retList.append(m_alteryxYXDB.m_recordInfo[i]->GetAsBool(rec).value);
					break;
				case SRC::E_FieldType::E_FT_Byte:
				case SRC::E_FieldType::E_FT_Int16:
				case SRC::E_FieldType::E_FT_Int32:
					retList.append(m_alteryxYXDB.m_recordInfo[i]->GetAsInt32(rec).value);
					break;
				case SRC::E_FieldType::E_FT_Int64:
					retList.append(m_alteryxYXDB.m_recordInfo[i]->GetAsInt64(rec).value);
					break;
				case SRC::E_FieldType::E_FT_FixedDecimal:
				case SRC::E_FieldType::E_FT_Float:
				case SRC::E_FieldType::E_FT_Double:
					retList.append(m_alteryxYXDB.m_recordInfo[i]->GetAsDouble(rec).value);
					break;

				case SRC::E_FieldType::E_FT_WString:
				case SRC::E_FieldType::E_FT_V_WString:
				case SRC::E_FieldType::E_FT_Date:
				case SRC::E_FieldType::E_FT_Time:
				case SRC::E_FieldType::E_FT_DateTime:
				{
					SRC::TFieldVal<SRC::WStringVal> wVal = m_alteryxYXDB.m_recordInfo[i]->GetAsWString(rec);
					if (wVal.bIsNull)
					{
						boost::python::object null{};
						retList.append(null);
					}
					else
					{
						SRC::AString utf8String = SRC::ConvertToAStringUtf8(wVal.value.pValue);
						retList.append(boost::python::str{ utf8String.c_str(),utf8String.Length() });

					}
					break;
				}
				case SRC::E_FieldType::E_FT_String:
				case SRC::E_FieldType::E_FT_V_String:
				{
					SRC::TFieldVal<SRC::AStringVal> aVal = m_alteryxYXDB.m_recordInfo[i]->GetAsAString(rec);
					if (aVal.bIsNull)
					{
						boost::python::object null{};
						retList.append(null);
					}
					else
					{
						//holy cow is this backwords.... but make sure we have a UTF8 string... so send it into UTF-16, then convert it back (coming back it ALWAYS goes to UTF-8)
						SRC::WString utf16String = SRC::ConvertToWString(aVal.value.pValue);
						SRC::AString utf8String = SRC::ConvertToAStringUtf8(utf16String);
						retList.append(boost::python::str{ utf8String.c_str(),utf8String.Length() });

					}
					break;
				}
				case SRC::E_FieldType::E_FT_Blob:
					break;




				}
			}

		}
		//else, we are done, return an empty list and slap the user with a fish.

		return retList;
	}

};

BOOST_PYTHON_MODULE(Python_AlteryxYXDB)
{
	using namespace boost::python;
	using Alteryx::OpenYXDB::Open_AlteryxYXDB;
	using boost::shared_ptr;

	const auto translator = [](const SRC::Error& e)
	{
		PyErr_SetString(PyExc_RuntimeError, SRC::ConvertToAString(e.GetErrorDescription()));
	};

	register_exception_translator<SRC::Error>(translator);

	enum_<SRC::E_FieldType>("FieldType")
		.value("unknown", SRC::E_FT_Unknown)
		.value("bool", SRC::E_FT_Bool)
		.value("byte", SRC::E_FT_Byte)
		.value("int16", SRC::E_FT_Int16)
		.value("int32", SRC::E_FT_Int32)
		.value("int64", SRC::E_FT_Int64)
		.value("fixeddecimal", SRC::E_FT_FixedDecimal)
		.value("float", SRC::E_FT_Float)
		.value("double", SRC::E_FT_Double)
		.value("string", SRC::E_FT_String)
		.value("wstring", SRC::E_FT_WString)
		.value("v_string", SRC::E_FT_V_String)
		.value("v_wstring", SRC::E_FT_V_WString)
		.value("date", SRC::E_FT_Date)
		.value("time", SRC::E_FT_Time)
		.value("datetime", SRC::E_FT_DateTime)
		.value("blob", SRC::E_FT_Blob)
		.value("spatialobj", SRC::E_FT_SpatialObj)
		;

	class_<SRC::Python::ConstRecordRef, boost::shared_ptr<SRC::Python::ConstRecordRef>>("RecordRef", no_init);

	class_<RecordCreator, shared_ptr<RecordCreator>>("RecordCreator", no_init)
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
			, arg("var_data_size") = 0
			, "Sets the capacity in bytes for variable-length data in this record to `var_data_size`."
		)
		;

	class_<Field>("field", no_init)
		.add_property("size", &Field::Size, "The size of the field in bytes.")
		.add_property("type", &Field::Type, "The type of the field.")
		.add_property("scale", &Field::Scale, "The scale of the field.")
		.add_property("name", &Field::Name, "The name of the field.")
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

	class_<RecordInfo, shared_ptr<RecordInfo>>("record_info")
		.def("__len__", &RecordInfo::NumFields)
		.def("num_fields", &RecordInfo::NumFields)
		.def("__getitem__", &RecordInfo::At)
		.def("at", &RecordInfo::At)
		.def("add_field_from_xml", &RecordInfo::AddFieldFromXml)
		.def(
			"add_field", &RecordInfo::AddField
			, (arg("field_name"), arg("field_type"), arg("size") = 0, arg("scale") = 0, arg("source") = "", arg("description") = "")
		)
		.def(
			"get_record_xml_meta_data", &RecordInfo::GetRecordXmlMetaData
			, arg("bIncludeSource") = true
		)
		.def("init_from_xml", &RecordInfo::InitFromXml)
		.def("construct_record_creator", &RecordInfo::ConstructRecordCreator)
		.def("get_field_num", &RecordInfo::GetFieldNum)
		.def("get_field_by_name", &RecordInfo::GetFieldByName)
		;

	class_<AlteryxYXDB, boost::noncopyable>("AlteryxYXDB")
		.def("create", &AlteryxYXDB::create)
		.def("open", &AlteryxYXDB::open)
		.def("append_record", &AlteryxYXDB::append)
		.def("read_record", &AlteryxYXDB::readRow)
		;


	class_<foo, shared_ptr<foo>>("foo")
		.def("int_method", &foo::int_method)
		.def("str_method", &foo::str_method)
		.def("print_method", &foo::print_method)
		;

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
	cout << "Hello, " << std::string{ boost::python::extract<std::string>(name) } << "!\n";
}
