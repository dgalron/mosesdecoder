#pragma once

#include <vector>
#include "moses/InputPath.h"

namespace Moses
{
class HHInputPathSCFG : public InputPath
{
  std::vector<Word> m_nonTerms;
  std::vector<HHInputPathSCFG*> m_suffixes;

public:
  HHInputPathSCFG(const Phrase &phrase,
                const NonTerminalSet &sourceNonTerms,
                const WordsRange &range,
                const HHInputPathSCFG *prevPath,
                const ScorePair *inputScore);

  const std::vector<Word> &GetNonTerms() const
  { return m_nonTerms; }

};

}

