#pragma once

#include <vector>

namespace Moses
{
class Word;

class HHChartCell
{
public:
	HHChartCell();
	virtual ~HHChartCell();

	const std::vector<Word> &GetNonTerms() const;

protected:
};

}

