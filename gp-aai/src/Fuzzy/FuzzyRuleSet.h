#pragma once

#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"


using std::vector;

class FuzzyRuleSet
{
private:
	

public:
	vector<FuzzyRule*> Rules;

	//standaard constructor + destructor
	FuzzyRuleSet();
	~FuzzyRuleSet();

	// functies
	double Calculate(double a, double b);
};
