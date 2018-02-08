#include "../stdafx.h"

#include "Field.h"
#include "RecordCreator.h"

#include "../SrcLib_Replacement.h"

using namespace boost;
using namespace boost::python;
using namespace SRC;

const FieldBase *
Field::get() const
{
	assert(m_ptrField != nullptr);
	return m_ptrField;
}

Field::Field(const FieldBase* field)
	: m_ptrField{field}
{
}

uint32_t
Field::Size() const
{
	return get()->m_nSize;
}

E_FieldType
Field::Type() const
{
	return get()->m_ft;
}

int
Field::Scale() const
{
	return get()->m_nScale;
}

str
Field::Name() const
{
	const auto ansi_name = ConvertToAString(get()->GetFieldName());
	return {ansi_name.c_str(), ansi_name.Length()};
}

str
Field::Source() const
{
	const auto ansi_source = ConvertToAString(get()->GetSource());
	return {ansi_source.c_str(), ansi_source.Length()};
}

str
Field::Description() const
{
	const auto ansi_desc = ConvertToAString(get()->GetDescription());
	return {ansi_desc.c_str(), ansi_desc.Length()};
}

template<typename FieldVal>
object
return_nullable(const FieldVal& val)
{
	if (val.bIsNull)
	{
		return {};
	}
	return object{val.value};
}

object
Field::GetAsBool(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return return_nullable(get()->GetAsBool(record_ref));
}

void
Field::SetFromBool(boost::shared_ptr<RecordCreator> record, const bool new_val) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetFromBool(record->m_ptrRecord.Get(), new_val);
}

object
Field::GetAsInt32(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return return_nullable(get()->GetAsInt32(record_ref));
}

void
Field::SetFromInt32(boost::shared_ptr<RecordCreator> record, int32_t value) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetFromInt32(record->m_ptrRecord.Get(), value);
}

object
Field::GetAsInt64(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return return_nullable(get()->GetAsInt64(record_ref));
}

void
Field::SetFromInt64(boost::shared_ptr<RecordCreator> record, int64_t value) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetFromInt64(record->m_ptrRecord.Get(), value);
}

object
Field::GetAsDouble(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return return_nullable(get()->GetAsDouble(record_ref));
}

void
Field::SetFromDouble(boost::shared_ptr<RecordCreator> record, double value) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetFromDouble(record->m_ptrRecord.Get(), value);
}

template<typename FieldVal>
object
return_nullable_string(const FieldVal& val)
{
	if (val.bIsNull)
	{
		return {};
	}

	const auto utf8_str = ConvertToAString(val.value.pValue);
	return object{str{utf8_str.c_str(), utf8_str.Length()}};
}

object
Field::GetAsString(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return return_nullable_string(get()->GetAsWString(record_ref));
}

void
Field::SetFromString(boost::shared_ptr<RecordCreator> record, raw_utf8_str value) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetFromString(record->m_ptrRecord.Get(), ConvertToWString(value));
}

bool
Field::GetNull(const RecordData *const record_ref) const
{
	assert(record_ref != nullptr);
	return get()->GetNull(record_ref);
}

void
Field::SetNull(boost::shared_ptr<RecordCreator> record) const
{
	assert(record->m_ptrRecord.Get() != nullptr);
	get()->SetNull(record->m_ptrRecord.Get());
}
