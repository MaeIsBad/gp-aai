#pragma once

#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"




class FuzzyRuleSet
{
private:
	

public:
	Vector<FuzzyRule*> Rules;

	//standaard constructor + destructor
	FuzzyRuleSet();
	~FuzzyRuleSet();

	// functies
	double Calculate(double a, double b);
};