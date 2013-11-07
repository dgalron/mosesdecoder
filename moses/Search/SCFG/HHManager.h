#pragma once

#include "HHChartCells.h"
#include "HHInputPathSCFG.h"

namespace Moses
{
class InputType;

class HHManager
{
  typedef std::vector<HHInputPathSCFG> InputPathListSCFG;
public:
	HHManager(InputType const& source);
	virtual ~HHManager();


protected:
	  const InputType &m_source;
	  HHChartCells m_cells;
	  InputPathListSCFG m_inputPathList;


};

}

