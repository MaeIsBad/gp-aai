#pragma once

#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"




class FuzzySet
{
private:

public:
	Vector<FuzzyVariable*> Variables;

	//standaard constructor + destructor
	FuzzySet();
	~FuzzySet();

	// functies
	void Add(FuzzyVariable* a);
	vecotr<double> Fuzzify(double x);
	vector<double> DeFuzzify(double y);
};
