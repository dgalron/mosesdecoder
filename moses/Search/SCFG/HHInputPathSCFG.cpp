#include "HHInputPathSCFG.h"

namespace Moses
{

HHInputPathSCFG::HHInputPathSCFG(const Phrase &phrase,
                const NonTerminalSet &sourceNonTerms,
                const WordsRange &range,
                const HHInputPathSCFG *prevPath,
                const ScorePair *inputScore)
:InputPath(phrase, sourceNonTerms, range, prevPath, inputScore)
{

}


}

