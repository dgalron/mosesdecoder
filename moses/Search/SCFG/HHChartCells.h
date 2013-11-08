#pragma once

#include <vector>
#include "HHChartCell.h"

namespace Moses
{
class WordsRange;

class HHChartCells
{
  typedef std::vector<HHChartCell* > Inner;
	typedef std::vector<Inner> Coll;
public:
	HHChartCells(std::size_t size);
	virtual ~HHChartCells();

	const HHChartCell &GetCell(const WordsRange &range) const;

protected:
	std::size_t m_size;
  Coll m_cells;

};

}

