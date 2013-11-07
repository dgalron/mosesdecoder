#pragma once

#include <vector>
#include "HHChartCells.h"

namespace Moses
{
class InputType;
class HHInputPathSCFG;
class HHLookupManager;

class HHManager
{
  //typedef std::vector<HHInputPathSCFG*> InputPathListSCFG;
public:
	HHManager(InputType const& source);
	virtual ~HHManager();


protected:
	  const InputType &m_source;
	  HHChartCells m_cells;

	  std::vector<HHInputPathSCFG*> m_inputPathQueue;
	  std::vector<HHLookupManager*> m_ruleLookupManagers;

	  typedef std::vector< std::vector<HHInputPathSCFG*> > InputPathMatrix;
	  InputPathMatrix m_inputPathMatrix; /*< contains translation options */

	  void CreateInputPaths();
	  HHInputPathSCFG &GetInputPath(std::size_t startPos, std::size_t endPos);

	  void InitializeLookupManagers();
};

}

