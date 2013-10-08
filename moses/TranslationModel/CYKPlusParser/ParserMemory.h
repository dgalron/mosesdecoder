#pragma once

#include <unistd.h>
#include <vector>
#include "Parser.h"

namespace Moses
{

class Word;
class WordsRange;
class PhraseDictionaryMemory;
class PhraseDictionaryNodeMemory;

class ActiveChartItem
{
public:
	ActiveChartItem(const WordsRange &range,
					const PhraseDictionaryNodeMemory &node);

	const WordsRange &GetRange() const
	{ return m_range; }

	const PhraseDictionaryNodeMemory &GetNode() const
	{ return m_node; }

protected:
	const WordsRange &m_range;
	const PhraseDictionaryNodeMemory &m_node;
};

class ActiveChart
{
public:
	typedef std::vector<const ActiveChartItem*> Coll;

	ActiveChart()
	{}
	virtual ~ActiveChart();

	void Add(const ActiveChartItem *item)
	{
		m_coll.push_back(item);
	}

	const Coll &GetColl() const
	{ return m_coll; }

protected:
	Coll m_coll;

};

class ParserMemory : public Parser
{
public:
	ParserMemory(const PhraseDictionaryMemory &pt, size_t inputSize);

	void Init(const Word &word
			, const WordsRange &range);

	void Extend(const Word &word
			, const WordsRange &prevRange
			, const WordsRange &thisRange);

protected:
	const PhraseDictionaryMemory &m_pt;

	std::vector<ActiveChart> m_activeCharts;
};

}

