#include "ExportPythonSDK.h"

#pragma warning( push, 0 )
#define BOOST_PYTHON_STATIC_LIB
#include <boost\python\module.hpp>
#include <boost\python\def.hpp>
#include <boost\python\exception_translator.hpp>
#include <boost\exception\diagnostic_information.hpp>
#pragma warning( pop )

#include <iostream>

using std::exception;
using std::cerr;
using std::wcerr;
using boost::python::error_already_set;
using boost::current_exception_diagnostic_information;
// using SRC::Error;

// void
// export_enums()
// {
// 	using namespace SRC::Alteryx;
// 	enum STATUS : int
// 	{
// 		Flag_MediumPriority = STATUS_Flag_MediumPriority,
// 		Flag_HighPriority = STATUS_Flag_HighPriority,
// 		Flag_Transient = STATUS_Flag_Transient,
// 		Info = STATUS_Info,
// 		Warning = STATUS_Warning,
// 		Error = STATUS_Error,
// 		Complete = STATUS_Complete,
// 		FieldConversionError = STATUS_FieldConversionError,
// 		FieldConversionLimitReached = STATUS_FieldConversionLimitReached,
// 		Disabled = STATUS_Disabled,
// 		File_Input = STATUS_File_Input,
// 		File_Output = STATUS_File_Output,
// 		UpdateOutputMetaInfoXml = STATUS_UpdateOutputMetaInfoXml,
// 		UpdateOutputConfigXml = STATUS_UpdateOutputConfigXml,
// 		RequestAutoConfigRefresh = STATUS_RequestAutoConfigRefresh,
// 		DocumentTempFile = STATUS_DocumentTempFile,
// 		TempDirectory = STATUS_TempDirectory,
// 		File_Dependency = STATUS_File_Dependency,
// 		CacheTempFile = STATUS_CacheTempFile,
// 		LowDiskWarning = STATUS_LowDiskWarning,
// 		SafeModeError = STATUS_SafeModeError,
// 		RestrictedDataSetError = STATUS_RestrictedDataSetError,
// 		ChooseFromMultiple = STATUS_ChooseFromMultiple,
// 		PreviewFail = STATUS_PreviewFail,
// 		OutputFieldNames = STATUS_OutputFieldNames,
// 		OutputRecord = STATUS_OutputRecord,
// 		RecordCountString = STATUS_RecordCountString,
// 		SimultaneousTooMany = STATUS_SimultaneousTooMany,
// 		BrowseEverywhereFileName = STATUS_BrowseEverywhereFileName,
// 		DataProfiling = STATUS_DataProfiling
// 	};

// 	using namespace boost::python;
// 	enum_<STATUS>("Status")
// 		.value("info", STATUS::Info)
// 		.value("warning", STATUS::Warning)
// 		.value("error", STATUS::Error)
// 		.value("complete", STATUS::Complete)
// 		.value("field_conversion_error", STATUS::FieldConversionError)
// 		.value("field_conversion_limit_reached", STATUS::FieldConversionLimitReached)
// 		.value("disabled", STATUS::Disabled)
// 		.value("file_input", STATUS::File_Input)
// 		.value("file_output", STATUS::File_Output)
// 		.value("update_output_meta_info_xml", STATUS::UpdateOutputMetaInfoXml)
// 		.value("update_output_config_xml", STATUS::UpdateOutputConfigXml)
// 		.value("request_auto_config_refresh", STATUS::RequestAutoConfigRefresh)
// 		.value("document_temp_file", STATUS::DocumentTempFile)
// 		.value("temp_directory", STATUS::TempDirectory)
// 		.value("file_dependency", STATUS::File_Dependency)
// 		.value("cache_temp_file", STATUS::CacheTempFile)
// 		.value("low_disk_warning", STATUS::LowDiskWarning)
// 		.value("safe_mode_error", STATUS::SafeModeError)
// 		.value("restricted_data_set_error", STATUS::RestrictedDataSetError)
// 		.value("choose_from_multiple", STATUS::ChooseFromMultiple)
// 		.value("preview_fail", STATUS::PreviewFail)
// 		.value("output_field_names", STATUS::OutputFieldNames)
// 		.value("output_record", STATUS::OutputRecord)
// 		.value("record_count_string", STATUS::RecordCountString)
// 		.value("simultaneous_too_many", STATUS::SimultaneousTooMany)
// 		.value("browse_everywhere_file_name", STATUS::BrowseEverywhereFileName)
// 		.value("data_profiling", STATUS::DataProfiling)
// 	;



// 	enum_<SRC::E_FieldType>("FieldType")
// 		.value("unknown", SRC::E_FT_Unknown)
// 		.value("bool", SRC::E_FT_Bool)
// 		.value("byte", SRC::E_FT_Byte)
// 		.value("int16", SRC::E_FT_Int16)
// 		.value("int32", SRC::E_FT_Int32)
// 		.value("int64", SRC::E_FT_Int64)
// 		.value("fixeddecimal", SRC::E_FT_FixedDecimal)
// 		.value("float", SRC::E_FT_Float)
// 		.value("double", SRC::E_FT_Double)
// 		.value("string", SRC::E_FT_String)
// 		.value("wstring", SRC::E_FT_WString)
// 		.value("v_string", SRC::E_FT_V_String)
// 		.value("v_wstring", SRC::E_FT_V_WString)
// 		.value("date", SRC::E_FT_Date)
// 		.value("time", SRC::E_FT_Time)
// 		.value("datetime", SRC::E_FT_DateTime)
// 		.value("blob", SRC::E_FT_Blob)
// 		.value("spatialobj", SRC::E_FT_SpatialObj)
// 	;

// 	enum_<SRC::GenericEngineBase::MessageType>("EngineMessageType")
// 		.value("error", SRC::GenericEngineBase::MessageType::MT_Error)
// 		.value("field_conversion_error", SRC::GenericEngineBase::MessageType::MT_FieldConversionError)
// 		.value("field_conversion_limit_reached", SRC::GenericEngineBase::MessageType::MT_FieldConversionLimitReached)
// 		.value("info", SRC::GenericEngineBase::MessageType::MT_Info)
// 		.value("safe_mode_error", SRC::GenericEngineBase::MessageType::MT_SafeModeError)
// 		.value("warning", SRC::GenericEngineBase::MessageType::MT_Warning)
// 	;
// }

// void
// export_exceptions()
// {
// 	const auto translator = [](const SRC::Error& e)
// 	{
// 		PyErr_SetString(PyExc_RuntimeError, SRC::ConvertToUtf8String(e.GetErrorDescriptionW()));
// 	};

// 	python::register_exception_translator<SRC::Error>(translator);
// }

// /**
// * This boost macro creates the main entry point that Python looks for: PyInit_AlteryxPythonSDK.
// *
// * Importing this module into the Python script results in the Python interpreter calling the
// * method PyInit_AlteryxPythonSDK().  When running in-process, this results in double-registration
// * of the boost::python object converters in its type registry, which in turn hinders debugging.
// *
// * That said, wrap the initialization methods in a call_once AND do not explicitly shut down the
// * interpreter via Py_EndInterpreter when running in-process.
// */
// BOOST_PYTHON_MODULE(AlteryxPythonSDK)
// {
// 	try
// 	{
// 		const auto ExportToPython = []() {
// 			python::docstring_options doc_options(true, true, false);

// 			export_enums();
// 			export_exceptions();
// 			export_field();
// 			export_record_info();
// 			export_record_creator();
// 			export_record_ref();
// 			export_record_copier();
// 			export_engine();
// 			export_output_anchor();
// 			export_output_anchor_manager();
// 		};
// 		static std::once_flag export_once;
// 		std::call_once(export_once, ExportToPython);
// 	}
// 	catch(const exception& exc)
// 	{
// 		cerr
// 			<< "std::exception: "
// 			<< exc.what()
// 			<< '\n';
// 	}
// 	catch(const error_already_set&)
// 	{
// 		cerr
// 			<< "boost::python::error_already_set: "
// 			<< SRC::ConvertToUtf8String(SRC::Python::LastErrorStr())
// 			<< '\n';
// 	}
// 	catch(const Error& exc)
// 	{
// 		cerr
// 			<< "SRC::Error: "
// 			<< exc.GetErrorDescriptionA()
// 			<< '\n';
// 	}
// 	catch(...)
// 	{
// 		cerr
// 			<< "unknown exception: "
// 			<< current_exception_diagnostic_information()
// 			<< '\n';
// 	}
// }

char const* yay()
{
  return "Yay!";
}

BOOST_PYTHON_MODULE(Python_AlteryxYXDB)
{
  using namespace boost::python;
  def("yay", yay);
}
