#pragma once

#pragma warning( push, 0 )
#include "../SrcLib_Replacement.h"
#include "../RecordLib/Record.h"
#include "../Open_AlteryxYxdb.h"
#include <napi.h>
#pragma warning( pop )

namespace node {

class Field : public Napi::ObjectWrap<Field>
{
  const SRC::FieldBase* m_field;
public:
	static void
	Initialize(Napi::Env&, Napi::Object&);

	static Napi::FunctionReference constructor;

	Field(const Napi::CallbackInfo &);
	~Field();

	Napi::Value
	GetFieldName(const Napi::CallbackInfo &);

	Napi::Value
	GetAsNumber(const Napi::CallbackInfo &);
	
	void
	SetFromNumber(const Napi::CallbackInfo &);
};

class RecordCreator : public Napi::ObjectWrap<RecordCreator>
{
public:
	SRC::SmartPointerRefObj<SRC::Record> m_record;

	static void
	Initialize(Napi::Env&, Napi::Object&);

	static Napi::FunctionReference constructor;

	RecordCreator(const Napi::CallbackInfo &);
	~RecordCreator();

	void
	Reset(const Napi::CallbackInfo &info);

	Napi::Value
	FinalizeRecord(const Napi::CallbackInfo &info);
};

class RecordInfo : public Napi::ObjectWrap<RecordInfo>
{
	SRC::RecordInfo m_recordInfo;

public:
	static void
	Initialize(Napi::Env&, Napi::Object&);

	static Napi::FunctionReference constructor;

	RecordInfo(const Napi::CallbackInfo &);
	~RecordInfo();

	void
	AddField(const Napi::CallbackInfo &);

	Napi::Value
	GetField(const Napi::CallbackInfo &);

	Napi::Value
	GetRecordXmlMetaData(const Napi::CallbackInfo &);

	Napi::Value
	GetRecordCreator(const Napi::CallbackInfo &);
};

class AlteryxYXDB : public Napi::ObjectWrap<AlteryxYXDB>
{
	Alteryx::OpenYXDB::Open_AlteryxYXDB m_alteryxYXDB{};

public:
	static void
	Initialize(Napi::Env&, Napi::Object&);

	static Napi::FunctionReference constructor;

	AlteryxYXDB(const Napi::CallbackInfo &);
	~AlteryxYXDB();

	void
	Close(const Napi::CallbackInfo &);

	void
	Open(const Napi::CallbackInfo &);

	void
	Create(const Napi::CallbackInfo &);

	//const RecordData * ReadRecord();
	void
	AppendRecord(const Napi::CallbackInfo &);

	//__int64 GetNumRecords();

	//void GoRecord(__int64 nRecord = 0);

	//WString GetRecordXmlMetaData();
};

}
