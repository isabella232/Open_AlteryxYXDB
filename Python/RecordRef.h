#pragma once

namespace SRC {

struct RecordData;

namespace Python {

struct ConstRecordRef
{
	const RecordData* m_ptrRecordData{};

	ConstRecordRef() = default;
	ConstRecordRef(const RecordData*);
};

}/*end namespace Python*/ }//end namespace SRC
