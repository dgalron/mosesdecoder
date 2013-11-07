#include "HHChartCells.h"

using namespace std;

namespace Moses
{

HHChartCells::HHChartCells(std::size_t size)
:m_cells(size)
{
  for (size_t startPos = 0; startPos < size; ++startPos) {
    Inner &inner = m_cells[startPos];
    inner.reserve(size - startPos);
    for (size_t endPos = startPos; endPos < size; ++endPos) {
      inner.push_back(new HHChartCell());
    }
  }

}

HHChartCells::~HHChartCells()
{

}


} // namespace
