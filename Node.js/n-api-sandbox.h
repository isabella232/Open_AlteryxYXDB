#pragma once

#pragma warning( push, 0 )
#include "../SrcLib_Replacement.h"
#include "../RecordLib/Record.h"
#include <napi.h>
#pragma warning( pop )

namespace node {

class RecordInfo : public Napi::ObjectWrap<RecordInfo>
{
	SRC::RecordInfo m_recordInfo;

public:
	static void
		Initialize(Napi::Env&, Napi::Object&);

	RecordInfo(const Napi::CallbackInfo&);
	~RecordInfo();

	void
		AddField(const Napi::CallbackInfo&);

	Napi::Value
		GetRecordXmlMetaData(const Napi::CallbackInfo&);
};

}
