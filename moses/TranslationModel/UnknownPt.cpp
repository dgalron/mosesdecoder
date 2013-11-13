// vim:tabstop=2
#include "UnknownPt.h"
#include "moses/DecodeGraph.h"

using namespace std;

namespace Moses
{
UnknownPt::UnknownPt(const std::string &line)
  : PhraseDictionary(line)
{
  ReadParameters();
}

void UnknownPt::CleanUpAfterSentenceProcessing(const InputType& source)
{
  RemoveAllInColl(m_allTPColl);
}

void UnknownPt::GetTargetPhraseCollectionBatch(const InputPathList &inputPathQueue) const
{
  size_t maxSpan = GetDecodeGraph().GetMaxChartSpan();

  InputPathList::const_iterator iter;
  for (iter = inputPathQueue.begin(); iter != inputPathQueue.end(); ++iter) {
    InputPath &inputPath = **iter;
    const Phrase &sourcePhrase = inputPath.GetPhrase();
    if (sourcePhrase.GetSize() <= maxSpan) {
		TargetPhrase *tp = CreateTargetPhrase(inputPath.GetPhrase());
		TargetPhraseCollection *tpColl = new TargetPhraseCollection();
		tpColl->Add(tp);

		m_allTPColl.push_back(tpColl);
		inputPath.SetTargetPhrases(*this, tpColl, NULL);
    }
  }
}

TargetPhrase *UnknownPt::CreateTargetPhrase(const Phrase &sourcePhrase) const
{
	cerr << sourcePhrase << endl;
  // create a target phrase from the 1st word of the source, prefix with 'UnknownPt:'
  CHECK(sourcePhrase.GetSize());
  CHECK(m_output.size() == 1);

  string str = sourcePhrase.GetWord(0).GetFactor(0)->GetString().as_string();
  str = "UnknownPt:" + str;

  TargetPhrase *tp = new TargetPhrase();
  Word &word = tp->AddWord();
  word.CreateFromString(Output, m_output, str, false);

  // score for this phrase table
  vector<float> scores(m_numScoreComponents, 1.3);
  tp->GetScoreBreakdown().PlusEquals(this, scores);

  // score of all other ff when this rule is being loaded
  tp->Evaluate(sourcePhrase, GetFeaturesToApply());

  return tp;
}

ChartRuleLookupManager* UnknownPt::CreateRuleLookupManager(const ChartParser &parser,
    const ChartCellCollectionBase &cellCollection)
{
  //return new ChartRuleLookupManagerSkeleton(parser, cellCollection, *this);
}

TO_STRING_BODY(UnknownPt);

// friend
ostream& operator<<(ostream& out, const UnknownPt& phraseDict)
{
  return out;
}

}
