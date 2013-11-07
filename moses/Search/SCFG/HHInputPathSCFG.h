#pragma once

#include "moses/InputPath.h"

namespace Moses
{
class HHInputPathSCFG : public InputPath
{
public:
  HHInputPathSCFG(const Phrase &phrase,
                const NonTerminalSet &sourceNonTerms,
                const WordsRange &range,
                const HHInputPathSCFG *prevPath,
                const ScorePair *inputScore);

};

}

