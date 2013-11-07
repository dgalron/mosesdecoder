#include "HHManager.h"
#include "moses/InputType.h"

namespace Moses
{
HHManager::HHManager(InputType const& source)
:m_source(source)
,m_cells(source.GetSize())
{

}

HHManager::~HHManager()
{

}

}



