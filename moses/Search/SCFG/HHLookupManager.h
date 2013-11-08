#pragma once
#include <vector>

namespace Moses
{
class HHInputPathSCFG;
class HHChartCells;

class HHLookupManager
{
public:
  virtual void Lookup(HHInputPathSCFG &path, const HHChartCells &cells) = 0;
};

//////////////////////////////////////////////////////////////

class PhraseDictionaryMemory;
class PhraseDictionaryNodeMemory;
class InputPath;

class HHLookupManagerMemory : public HHLookupManager
{
  class HHActiveChartItemMemory
  {
  public:
    const InputPath *m_path;
    const PhraseDictionaryNodeMemory &m_node;

    HHActiveChartItemMemory(const InputPath *path, const PhraseDictionaryNodeMemory &node)
    :m_path(path)
    ,m_node(node)
    {}

  };

public:
  HHLookupManagerMemory(); // do not implement
  HHLookupManagerMemory(const PhraseDictionaryMemory &pt, std::size_t size);

  void Lookup(HHInputPathSCFG &path, const HHChartCells &cells);

protected:
  const PhraseDictionaryMemory &m_pt;

  typedef std::vector<HHActiveChartItemMemory*> ActiveChartList;
  typedef std::vector<ActiveChartList> ActiveChart;
  ActiveChart m_activeItems;

  void LookupNonTerm(HHInputPathSCFG &path);


};

}

