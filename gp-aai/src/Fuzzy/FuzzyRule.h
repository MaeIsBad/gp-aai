#pragma once

#include "FuzzyVariable.h"




class FuzzyRule
{
private:
	FuzzyVariable Antecedent1;
	FuzzyVariable Antecedent2;
	FuzzyVariable Concequent;

	enum Operator(AND, OR);

public:

	//standaard constructor + destructor
	FuzzyRule();
	~FuzzyRule();

	// functies
	double Calculate(double a, double b);
};

FuzzyRule operator AND(const FuzzyRule r1, constFuzzyRule r2);