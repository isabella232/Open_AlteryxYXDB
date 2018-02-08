#pragma once

#include "../SrcLib_Replacement.h"

namespace SRC {
class Record;
struct RecordData;
}

struct RecordCreator
{
	SRC::SmartPointerRefObj<SRC::Record> m_ptrRecord{};
	RecordCreator(SRC::SmartPointerRefObj<SRC::Record>);

	auto FinalizeRecord() const -> const SRC::RecordData *const;

	auto GetVarDataSize() -> int32_t;
	auto Reset(int32_t nVarDataSize = 0) -> void;
};