#define _WINSOCKAPI_
#pragma warning( push, 0 )
#include "../stdafx.h"
#pragma warning( pop )

#include "n-api-sandbox.h"

#pragma warning( push, 0 )
#include <napi-thread-safe-callback.hpp>
#pragma warning( pop )

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::exception;
using std::move;
using std::thread;
using std::vector;

namespace std { namespace chrono { } namespace this_thread { } }

namespace chrono = std::chrono;
namespace this_thread = std::this_thread;

using namespace SRC;


#define DO_LOGGING(x) \
{ \
	std::stringstream s; \
	s << x << '\n'; \
	std::cout << s.str(); \
}

namespace node {

std::once_flag field_once{};
Napi::FunctionReference Field::constructor{};

void
Field::Initialize(Napi::Env &env, Napi::Object &target) {
	std::call_once(field_once, [&env, &target]{
		auto temp_ctor{DefineClass(env, "Field",{
			InstanceMethod("get_field_name", &Field::GetFieldName)
		})};
		constructor = Persistent(temp_ctor);
		constructor.SuppressDestruct();
		target.Set("RecordInfo", temp_ctor);
	});
}

Field::Field(const Napi::CallbackInfo &info)
	: Napi::ObjectWrap<Field>{info}
	, m_field{info[0].As<Napi::External<FieldBase>>().Data()}
{
}

Field::~Field()
{
}

Napi::Value
Field::GetFieldName(const Napi::CallbackInfo &info)
{
	return Napi::String::New(info.Env(), ConvertToAString(m_field->GetFieldName()).c_str());
}

Napi::Value
Field::GetAsNumber(const Napi::CallbackInfo &info)
{
	if (!info[0].IsNumber())
	{
		throw Napi::Error::New(info.Env(), "record must be passed");
	}
	try
	{
		return Napi::Number::New(
			info.Env()
			, m_field->GetAsDouble(reinterpret_cast<const RecordData *>(info[0].As<Napi::Number>().Int64Value())).value
		);
	}
	catch (Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
	return {};
}

void
Field::SetFromNumber(const Napi::CallbackInfo &info)
{
	if (!info[0].IsObject())
	{
		throw Napi::Error::New(info.Env(), "record creator must be passed");
	}
	if (!info[1].IsNumber())
	{
		throw Napi::Error::New(info.Env(), "number must be passed");
	}

	try
	{
		m_field->SetFromDouble(
			info[0].As<Napi::External<RecordCreator>>().Data()->m_record.Get()
			, info[1].As<Napi::Number>().DoubleValue()
		);
	}
	catch (Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
}

std::once_flag record_creator_once{};
Napi::FunctionReference RecordCreator::constructor{};

void RecordCreator::Initialize(Napi::Env &env, Napi::Object &target)
{
	std::call_once(record_creator_once, [&env, &target] {
		auto ctor{ DefineClass(env, "RecordCreator",{
			InstanceMethod("reset", &RecordCreator::Reset)
			, InstanceMethod("finalize_record", &RecordCreator::FinalizeRecord)
		}) };

		constructor = Persistent(ctor);
		constructor.SuppressDestruct();
		target.Set("RecordCreator", ctor);
	});
}

RecordCreator::RecordCreator(const Napi::CallbackInfo &info)
	: Napi::ObjectWrap<RecordCreator>{ info }
	, m_record{ *info[0].As<Napi::External<SmartPointerRefObj<Record>>>().Data() }
{
}

RecordCreator::~RecordCreator() {}

void
RecordCreator::Reset(const Napi::CallbackInfo &/*info*/)
{
	m_record->Reset();
}

Napi::Value
RecordCreator::FinalizeRecord(const Napi::CallbackInfo &info)
{
#pragma warning (suppress: 4244 )
	return Napi::Number::New(info.Env(), reinterpret_cast<ptrdiff_t>(m_record->GetRecord()));
}

std::once_flag record_info_once{};
Napi::FunctionReference RecordInfo::constructor{};

void
RecordInfo::Initialize(Napi::Env &env, Napi::Object &target) {
	std::call_once(record_info_once, [&env, &target] {
		auto ctor{ DefineClass(env, "RecordInfo",{
			InstanceMethod("add_field", &RecordInfo::AddField)
			, InstanceMethod("get_record_xml_meta_data", &RecordInfo::GetRecordXmlMetaData)
			, InstanceMethod("get_field", &RecordInfo::GetField)
			, InstanceMethod("get_record_creator", &RecordInfo::GetRecordCreator)
		}) };
		
		constructor = Persistent(ctor);
		constructor.SuppressDestruct();
		target.Set("RecordInfo", ctor);
	});
}

RecordInfo::RecordInfo(const Napi::CallbackInfo &info)
	: Napi::ObjectWrap<RecordInfo>{info}
{
}

RecordInfo::~RecordInfo()
{
}

void
RecordInfo::AddField(const Napi::CallbackInfo &info)
{
	if (!info[0].IsString())
	{
		throw Napi::Error::New(info.Env(), "name must be passed");
	}
	if (!info[1].IsNumber())
	{
		throw Napi::Error::New(info.Env(), "type must be passed");
	}

	const auto name{ info[0].As<Napi::String>() };
	const auto type{ info[1].As<Napi::Number>() };

	m_recordInfo.AddField(SRC::RecordInfo::CreateFieldXml(ConvertToWString(name.Utf8Value().c_str()), static_cast<E_FieldType>(type.Int32Value())));
}

Napi::Value
RecordInfo::GetField(const Napi::CallbackInfo &info)
{
	if (!info[0].IsNumber())
	{
		throw Napi::Error::New(info.Env(), "type must be passed");
	}
	const auto idx{ info[0].As<Napi::Number>() };

	return Field::constructor.New({
		Napi::External<FieldBase>::New(
			info.Env()
			, const_cast<FieldBase*>(m_recordInfo[idx.Int32Value()])
		) 
	});
}

Napi::Value
RecordInfo::GetRecordXmlMetaData(const Napi::CallbackInfo &info)
{
	return Napi::String::New(info.Env(), ConvertToAString(m_recordInfo.GetRecordXmlMetaData()).c_str());
}

Napi::Value
RecordInfo::GetRecordCreator(const Napi::CallbackInfo &info)
{
	auto record{ m_recordInfo.CreateRecord() };
	return RecordCreator::constructor.New({
		Napi::External<SmartPointerRefObj<Record>>::New(
			info.Env()
			, &record
		)
	});
}

std::once_flag alteryx_yxdb_once{};
Napi::FunctionReference AlteryxYXDB::constructor{};

void AlteryxYXDB::Initialize(Napi::Env &env, Napi::Object &target)
{
	std::call_once(alteryx_yxdb_once, [&env, &target] {
		auto ctor{ DefineClass(env, "AlteryxYXDB",{
			InstanceMethod("close", &AlteryxYXDB::Close)
			, InstanceMethod("open", &AlteryxYXDB::Open)
			, InstanceMethod("create", &AlteryxYXDB::Create)
		}) };

		constructor = Persistent(ctor);
		constructor.SuppressDestruct();
		target.Set("AlteryxYXDB", ctor);
	});
}

AlteryxYXDB::AlteryxYXDB(const Napi::CallbackInfo &info)
	: Napi::ObjectWrap<AlteryxYXDB>{ info }
{
}

AlteryxYXDB::~AlteryxYXDB() {}

void AlteryxYXDB::Close(const Napi::CallbackInfo &/*info*/)
{
	try
	{
		m_alteryxYXDB.Close();
	}
	catch (Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
}

void AlteryxYXDB::Open(const Napi::CallbackInfo &info)
{
	if (!info[0].IsString())
	{
		throw Napi::Error::New(info.Env(), "file name must be passed");
	}
	try
	{
		m_alteryxYXDB.Open(ConvertToWString(info[0].As<Napi::String>().Utf8Value().c_str()));

	}
	catch(Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
}

void AlteryxYXDB::Create(const Napi::CallbackInfo &info)
{
	if (!info[0].IsString())
	{
		throw Napi::Error::New(info.Env(), "file name must be passed");
	}
	if (!info[1].IsString())
	{
		throw Napi::Error::New(info.Env(), "record info XML must be passed");
	}
	try
	{
		m_alteryxYXDB.Create(
			ConvertToWString(info[0].As<Napi::String>().Utf8Value().c_str())
			, ConvertToWString(info[1].As<Napi::String>().Utf8Value().c_str())
		);
	}
	catch (Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
}

void AlteryxYXDB::AppendRecord(const Napi::CallbackInfo &info)
{
	if (!info[0].IsNumber())
	{
		throw Napi::Error::New(info.Env(), "record must be passed");
	}
	try
	{
		m_alteryxYXDB.AppendRecord(
			reinterpret_cast<const RecordData *>(info[0].As<Napi::Number>().Int64Value())
		);
	}
	catch (Error e)
	{
		std::wcout << e.GetErrorDescription() << '\n';
	}
}

}

Napi::Object
Init(Napi::Env env, Napi::Object exports) {
	node::AlteryxYXDB::Initialize(env, exports);
	node::Field::Initialize(env, exports);
	node::RecordInfo::Initialize(env, exports);

	return exports;
}

NODE_API_MODULE(addon, Init);
