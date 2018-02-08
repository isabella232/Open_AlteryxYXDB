#include "../stdafx.h"

#include "RecordInfo.h"

#include "Field.h"
#include "RecordCreator.h"

#include "../SrcLib_Replacement.h"

#include <boost/make_shared.hpp>

using namespace boost;
using namespace boost::python;
using SRC::ConvertToWString;
using SRC::String;
using SRC::E_FieldType;

RecordInfo::RecordInfo()
	: m_recordInfo{}
{
}

uint32_t
RecordInfo::NumFields() const
{
	return m_recordInfo.NumFields();
}

Field
RecordInfo::At(const uint32_t nFieldIndex)
{
	if(m_recordInfo.NumFields() <= nFieldIndex)
	{
		throw std::runtime_error("");
	}
	return m_recordInfo[nFieldIndex];
}

Field
RecordInfo::AddFieldFromXml(raw_utf8_str strXmlTagField, raw_utf8_str strNamePrefix/* = nullptr*/)
{
	if (strNamePrefix != nullptr)
	{
		return m_recordInfo.AddField(
			ConvertToWString(strXmlTagField)
			, ConvertToWString(strNamePrefix)
		);
	}

	return m_recordInfo.AddField(ConvertToWString(strXmlTagField));
}

Field
RecordInfo::AddField(
	raw_utf8_str strFieldName
	, E_FieldType ft
	, int32_t nSize/* = 0*/
	, int32_t nScale/* = 0*/
	, raw_utf8_str strSource/* = nullptr*/
	, raw_utf8_str strDescription/* = nullptr*/
)
{
	return m_recordInfo.AddField(SRC::RecordInfo::CreateFieldXml(
		ConvertToWString(strFieldName)
		, ft
		, nSize
		, nScale
		, ConvertToWString(strSource)
		, ConvertToWString(strDescription)
	));
}

str
RecordInfo::GetRecordXmlMetaData(bool bIncludeSource/* = true*/) const
{
	return {ConvertToAString(m_recordInfo.GetRecordXmlMetaData(bIncludeSource)).c_str()};
}

void
RecordInfo::InitFromXml(
	raw_utf8_str strXmlTag
	, raw_utf8_str strNamePrefix/* = nullptr*/
)
{
	if (strNamePrefix != nullptr)
	{
		m_recordInfo.InitFromXml(ConvertToWString(strXmlTag), ConvertToWString(strNamePrefix));
	}
	else
	{
		m_recordInfo.InitFromXml(ConvertToWString(strXmlTag), nullptr);
	}
}

shared_ptr<RecordCreator>
RecordInfo::ConstructRecordCreator() const
{
	return boost::make_shared<RecordCreator>(m_recordInfo.CreateRecord());
}

int32_t
RecordInfo::GetFieldNum(raw_utf8_str strField, bool bThrowError/* = true*/) const
{
	return m_recordInfo.GetFieldNum(ConvertToWString(strField), bThrowError);
}

object
RecordInfo::GetFieldByName(raw_utf8_str strField, bool bThrowError/* = true*/) const
{
	auto field = m_recordInfo.GetFieldByName(ConvertToWString(strField), bThrowError);
	if (field == NULL) {
		return object();
	}
	return object(Field{ field });
}
