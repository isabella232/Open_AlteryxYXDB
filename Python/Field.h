#pragma once

#include "../SrcLib_Replacement.h"
#include "../RecordLib/FieldBase.h"

#pragma warning( push, 0 )
#include <boost/python/object.hpp>
#include <boost/python/str.hpp>
#pragma warning( pop )

namespace SRC {
class FieldBase;
struct RecordData;
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
  GetAsBool(const SRC::RecordData *const) const;
	void
  SetFromBool(boost::shared_ptr<RecordCreator>, bool) const;

	boost::python::object
  GetAsInt32(const SRC::RecordData *const) const;
	void
  SetFromInt32(boost::shared_ptr<RecordCreator>, int32_t) const;

	boost::python::object
  GetAsInt64(const SRC::RecordData *const) const;
	void
  SetFromInt64(boost::shared_ptr<RecordCreator>, int64_t) const;

	boost::python::object
  GetAsDouble(const SRC::RecordData *const) const;
	void
  SetFromDouble(boost::shared_ptr<RecordCreator>, double) const;

	boost::python::object
  GetAsString(const SRC::RecordData *const) const;
	void
  SetFromString(boost::shared_ptr<RecordCreator>, raw_utf8_str) const;

	bool
  GetNull(const SRC::RecordData *const) const;
	void
  SetNull(boost::shared_ptr<RecordCreator>) const;
};
