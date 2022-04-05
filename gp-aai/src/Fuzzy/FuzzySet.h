#pragma once

#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"

using std::vector;


class FuzzySet
{
private:

public:
	vector<FuzzyVariable*> Variables;

	//standaard constructor + destructor
	FuzzySet();
	~FuzzySet();

	// functies
	void Add(FuzzyVariable* a);
	vector<double> Fuzzify(double x);
	vector<double> DeFuzzify(double y);
};
