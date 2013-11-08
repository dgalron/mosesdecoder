#include "HHInputPathSCFG.h"
#include "HHLookupManager.h"
#include "HHChartCells.h"
#include "HHChartCell.h"
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

void HHLookupManagerMemory::Lookup(HHInputPathSCFG &path, const HHChartCells &cells)
{
  const WordsRange &range = path.GetWordsRange();
  size_t startPos = range.GetStartPos();
  size_t endPos = range.GetEndPos();

  const ActiveChartList &activeList = m_activeItems[startPos];
  ActiveChartList &endActiveList = m_activeItems[endPos];

  // terminal
  const Word &lastWord = path.GetLastWord();

  // for each previous active items that end where we start, try to extend with term
  HHLookupManagerMemory::ActiveChartList::const_iterator iterActiveItem;
  for (iterActiveItem = activeList.begin(); iterActiveItem != activeList.end(); ++iterActiveItem) {
    const HHActiveChartItemMemory &activeItem = **iterActiveItem;
    const PhraseDictionaryNodeMemory &prevNode = activeItem.m_node;

    const PhraseDictionaryNodeMemory *nextNode = prevNode.GetChild(lastWord);
    if (nextNode) {
      // save it somewhere

      // save in active stack
      HHActiveChartItemMemory *item = new HHActiveChartItemMemory(&path, *nextNode);
      endActiveList.push_back(item);
    }
  }

  // 1 non-term that spans the entire path
  const std::vector<Word> &sourceNonTerms = path.GetNonTerms();
  const std::vector<Word> &targetNonTerms = cells.GetCell(range).GetNonTerms();

  for (size_t i = 0; i < sourceNonTerms.size(); ++i) {
    const Word &sourceNonTerm = sourceNonTerms[i];
    for (size_t j = 0; j < sourceNonTerms.size(); ++j) {
      const Word &targetNonTerm = targetNonTerms[i];

      const PhraseDictionaryNodeMemory &prevNode = m_pt.GetRootNode();
      const PhraseDictionaryNodeMemory *nextNode = prevNode.GetChild(sourceNonTerm, targetNonTerm);
      if (nextNode) {
        // save it somewhere

        // save in active stack
        HHActiveChartItemMemory *item = new HHActiveChartItemMemory(&path, *nextNode);
        endActiveList.push_back(item);
      }
    }
  }

  // non-term that DOESN'T spans the entire path
  LookupNonTerm(path);
}

void HHLookupManagerMemory::LookupNonTerm(HHInputPathSCFG &path)
{

}

}

