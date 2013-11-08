#pragma once

#include <vector>
#include "moses/InputPath.h"

namespace Moses
{
class HHInputPathSCFG : public InputPath
{
public:
  typedef std::pair<const HHInputPathSCFG*,const HHInputPathSCFG*> BiPath;

  HHInputPathSCFG(const Phrase &phrase,
                const NonTerminalSet &sourceNonTerms,
                const WordsRange &range,
                const HHInputPathSCFG *prevPath,
                const ScorePair *inputScore);

  const std::vector<Word> &GetNonTerms() const
  { return m_nonTerms; }
  const std::vector<BiPath> &GetSuffixes() const
  { return m_suffixes; }

  void AddSuffix(const HHInputPathSCFG &prefixPath, const HHInputPathSCFG &suffixPath)
  {
    BiPath obj(&prefixPath, &suffixPath);
    m_suffixes.push_back(obj);
  }

protected:
  std::vector<Word> m_nonTerms;
  std::vector<BiPath> m_suffixes;
};

}

