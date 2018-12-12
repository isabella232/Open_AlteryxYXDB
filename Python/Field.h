#pragma once

#include "../SrcLib_Replacement.h"
#include "../RecordLib/FieldBase.h"

#pragma warning( push, 0 )
#include <boost/python/object.hpp>
#include <boost/python/str.hpp>
#pragma warning( pop )

namespace SRC {
	class FieldBase;
	namespace Python
	{
		struct ConstRecordRef;
	}
}

namespace boost {
	template<typename T>
	class shared_ptr;
}

struct RecordCreator;
class RecordInfo;

class Field
{
	friend class ::RecordInfo;
	const SRC::FieldBase* m_ptrField{};

	const SRC::FieldBase*
		get() const;

	using raw_utf8_str = const char* const;
public:
	Field() = delete;
	Field(const SRC::FieldBase*);

	Field(const Field&) = default;

	uint32_t
		Size() const;

	SRC::E_FieldType
		Type() const;

	int
		Scale() const;

	boost::python::str
		Name() const;

	boost::python::str
		Source() const;

	boost::python::str
		Description() const;

	boost::python::object
		GetAsBool(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetFromBool(boost::shared_ptr<RecordCreator>, bool) const;

	boost::python::object
		GetAsInt32(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetFromInt32(boost::shared_ptr<RecordCreator>, int32_t) const;

	boost::python::object
		GetAsInt64(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetFromInt64(boost::shared_ptr<RecordCreator>, int64_t) const;

	boost::python::object
		GetAsDouble(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetFromDouble(boost::shared_ptr<RecordCreator>, double) const;

	boost::python::object
		GetAsString(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetFromString(boost::shared_ptr<RecordCreator>, raw_utf8_str) const;

	bool
		GetNull(boost::shared_ptr<SRC::Python::ConstRecordRef>) const;
	void
		SetNull(boost::shared_ptr<RecordCreator>) const;
};
