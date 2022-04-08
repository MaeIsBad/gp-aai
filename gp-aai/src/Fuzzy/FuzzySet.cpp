#include <iostream>
#include <vector>
#include "FuzzyRule.h"
#include "FuzzyVariable"
#include "FuzzyRuleSet.h"
#include "FuzzySet.h"


/*****************************************************/
// standaard constructor + destructor
FuzzySet::FuzzySet()
{
	FuzzyVariable = nullptr;
}

FuzzySet::~FuzzySet()
{

}



/*****************************************************/
// functies
void FuzzySet::Add(FuzzyVariable* a)
{
	FuzzyVariable::startA = FuzzyVariable::startA + a.startA;
	FuzzyVariable::startB = FuzzyVariable::startB + a.startB;

	FuzzyVariable::endA = FuzzyVariable::endA + a.endA;
	FuzzyVariable::endB = FuzzyVariable::endB + a.endB;
}

vector<double> FuzzySet::Fuzzify(double x)
{	
	return 0.0;
}

vector<double> FuzzySet::DeFuzzify(double y)
{
	return 0.0;
}

