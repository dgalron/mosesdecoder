#include "HHInputPathSCFG.h"
#include "HHLookupManager.h"
#include "moses/TranslationModel/PhraseDictionaryMemory.h"

using namespace std;

namespace Moses
{
HHLookupManagerMemory::HHLookupManagerMemory(const PhraseDictionaryMemory &pt, size_t size)
:m_pt(pt)
,m_activeItems(size)
{
  for (size_t i = 0; i < size; ++i) {
    HHActiveChartItemMemory *item = new HHActiveChartItemMemory(NULL, pt.GetRootNode());
    ActiveChartList &list = m_activeItems[i];
    list.push_back(item);
  }
}

void HHLookupManagerMemory::Lookup(HHInputPathSCFG &path)
{
  size_t startPos = path.GetWordsRange().GetStartPos();
  size_t endPos = path.GetWordsRange().GetEndPos();

  // terminal
  const Word &lastWord = path.GetLastWord();

  const ActiveChartList &activeList = m_activeItems[startPos];
  HHLookupManagerMemory::ActiveChartList::const_iterator iterActiveItem;
  for (iterActiveItem = activeList.begin(); iterActiveItem != activeList.end(); ++iterActiveItem) {
    const HHActiveChartItemMemory &activeItem = **iterActiveItem;
    const PhraseDictionaryNodeMemory &prevNode = activeItem.m_node;

    const PhraseDictionaryNodeMemory *nextNode = prevNode.GetChild(lastWord);
    if (nextNode) {
      // save it somewhere
    }
  }

  // non-term

}

}

