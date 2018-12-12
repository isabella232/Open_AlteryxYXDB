#pragma once

#include "../RecordLib/Record.h"

#pragma warning( push, 0 )
#include <boost/python/object.hpp>
#include <boost/python/str.hpp>
#pragma warning( pop )

class Field;
struct RecordCreator;

namespace boost {
template<typename T>
class shared_ptr;
}

class RecordInfo
{
	SRC::RecordInfo m_recordInfo{};

	using raw_utf8_str = const char* const;
public:
	RecordInfo();

	uint32_t NumFields() const;

	Field At(uint32_t nFieldIndex);

	Field AddFieldFromXml(raw_utf8_str strXmlTagField, raw_utf8_str strNamePrefix = nullptr);


  Field AddField(
		raw_utf8_str strFieldName
		, SRC::E_FieldType ft
		, int32_t nSize = 0
		, int32_t nScale = 0
		, raw_utf8_str strSource = nullptr
		, raw_utf8_str strDescription = nullptr
	);

	boost::python::str GetRecordXmlMetaData(bool bIncludeSource = true) const;

  void InitFromXml(raw_utf8_str strXmlTag, raw_utf8_str strNamePrefix = nullptr);
  

	boost::shared_ptr<RecordCreator> ConstructRecordCreator() const;

	int32_t GetFieldNum(raw_utf8_str strField, bool bThrowError = true) const;

  boost::python::object // ConstField or Python None
	  GetFieldByName(raw_utf8_str strField, bool bThrowError = true) const;

};
