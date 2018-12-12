#include "../stdafx.h"

#include <boost/smart_ptr/make_shared.hpp>
#include "RecordCreator.h"
#include "RecordRef.h"

#include "../RecordLib/Record.h"



using namespace SRC;

RecordCreator::RecordCreator(SmartPointerRefObj<SRC::Record> record)
	: m_ptrRecord(std::move(record))
{
}

boost::shared_ptr<SRC::Python::ConstRecordRef>
RecordCreator::FinalizeRecord() const
{
	return boost::make_shared<Python::ConstRecordRef>(m_ptrRecord->GetRecord());
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
