#include "HHManager.h"
#include "HHInputPathSCFG.h"
#include "HHLookupManager.h"
#include "moses/InputType.h"
#include "moses/Util.h"
#include "moses/StaticData.h"
#include "moses/TranslationModel/PhraseDictionary.h"
#include "util/check.hh"

using namespace std;

namespace Moses
{
HHManager::HHManager(InputType const& source)
:m_source(source)
,m_cells(source.GetSize())
{
  CreateInputPaths();
  InitializeLookupManagers();
}

HHManager::~HHManager()
{
  RemoveAllInColl(m_inputPathQueue);
}

void HHManager::CreateInputPaths()
{
  size_t size = m_source.GetSize();

  CHECK(m_source.GetType() == SentenceInput);

  m_inputPathMatrix.resize(size);
  for (size_t phaseSize = 1; phaseSize <= size; ++phaseSize) {
    for (size_t startPos = 0; startPos < size - phaseSize + 1; ++startPos) {
      size_t endPos = startPos + phaseSize -1;
      vector<HHInputPathSCFG*> &vec = m_inputPathMatrix[startPos];

      WordsRange range(startPos, endPos);
      Phrase subphrase(m_source.GetSubString(WordsRange(startPos, endPos)));
      const NonTerminalSet &labels = m_source.GetLabelSet(startPos, endPos);

      HHInputPathSCFG *path;
      if (range.GetNumWordsCovered() == 1) {
        path = new HHInputPathSCFG(subphrase, labels, range, NULL, NULL);
        vec.push_back(path);
      } else {
        const HHInputPathSCFG &prevPath = GetInputPath(startPos, endPos - 1);
        path = new HHInputPathSCFG(subphrase, labels, range, &prevPath, NULL);
        vec.push_back(path);
      }

      m_inputPathQueue.push_back(path);
    }
  }
}

HHInputPathSCFG &HHManager::GetInputPath(size_t startPos, size_t endPos)
{
  size_t offset = endPos - startPos;
  CHECK(offset < m_inputPathMatrix[startPos].size());
  return *m_inputPathMatrix[startPos][offset];
}

void HHManager::InitializeLookupManagers()
{
  size_t size = m_source.GetSize();

  const StaticData &staticData = StaticData::Instance();
  const std::vector<PhraseDictionary*> &dictionaries = staticData.GetPhraseDictionaries();
  m_ruleLookupManagers.reserve(dictionaries.size());

  for (std::vector<PhraseDictionary*>::const_iterator p = dictionaries.begin();
       p != dictionaries.end(); ++p) {

    const PhraseDictionary *dict = *p;
    PhraseDictionary *nonConstDict = const_cast<PhraseDictionary*>(dict);

    HHLookupManager *lookupMgr = nonConstDict->HHCreateLookupManager(size);
    m_ruleLookupManagers.push_back(lookupMgr);
  }

}

void HHManager::Process()
{
  // for each input path, use it to extend parse, and decode.
  // --> input path list must be in topological order
  InputPathListSCFG::iterator iterPath;
  for (iterPath = m_inputPathQueue.begin(); iterPath != m_inputPathQueue.end(); ++iterPath) {
    HHInputPathSCFG &path = **iterPath;

    // parse
    std::vector<HHLookupManager*>::iterator iterLookupMgr;
    for (iterLookupMgr = m_ruleLookupManagers.begin(); iterLookupMgr != m_ruleLookupManagers.end(); ++iterLookupMgr) {
      HHLookupManager &lookupMgr = **iterLookupMgr;
      lookupMgr.Lookup(path,m_cells);
    }

    // decode

  }

}

}



