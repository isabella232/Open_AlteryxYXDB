#include "../stdafx.h"

#include "RecordCreator.h"

#include "../RecordLib/Record.h"

using namespace SRC;

RecordCreator::RecordCreator(SmartPointerRefObj<SRC::Record> record)
	: m_ptrRecord(std::move(record))
{
}

const RecordData*
RecordCreator::FinalizeRecord() const
{
	return m_ptrRecord->GetRecord();
}

int32_t
RecordCreator::GetVarDataSize()
{
	return m_ptrRecord->GetVarDataSize();
}

void
RecordCreator::Reset(const int32_t nVarDataSize/* = 0*/)
{
	return m_ptrRecord->Reset(nVarDataSize);
}
