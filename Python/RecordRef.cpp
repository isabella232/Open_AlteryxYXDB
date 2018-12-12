

#include "RecordRef.h"
#include "../RecordLib/RecordObj.h"

namespace SRC { namespace Python {

ConstRecordRef::ConstRecordRef(const RecordData* data)
	: m_ptrRecordData{data}
{
}

}/*end namespace Python*/ }//end namespace SRC

