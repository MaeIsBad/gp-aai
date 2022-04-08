#pragma once
#include <iostream>
#include "FuzzyRule.h"



/*****************************************************/
// standaard constructor + destructor
FuzzyRule::FuzzyRule(FuzzyVariable Antecedent1, FuzzyVariable Antecedent2, FuzzyVariable Concequent, Operator o) {

	this->Antecedent1 = Antecedent1;
	this->Antecedent2 = Antecedent2;

	this->Concequent = Concequent;

	this->Operator = o;
}

FuzzyRule::~FuzzyRule()
{

}



/*****************************************************/
// functies
double FuzzyRule::Calculate(double a, double b)
{
	auto resultingAntecedent1 = this->Antecedent1.Fuzzify(a);
	auto resultingAntecedent2 = this->Antecedent2.Fuzzify(b);

	double resultingConcequent = -1;

	if (this->Operator == FuzzyOperator::AND) {
		if (resultingAntecedent1 > resultingAntecedent2) {

			resultingConcequent = resultingAntecedent1;
		}
		else {
			resultingConcequent = resultingAntecedent2;
		}
	}
	else if (this->Operator == FuzzyOperator::OR) {
		if (resultingAntecedent1 < resultingAntecedent2) {

			resultingConcequent = resultingAntecedent1;
		}
		else {
			resultingConcequent = resultingAntecedent2;
		}
	}

	return resultingConcequent;
}
