#include <iostream>
#include "FuzzyVariable.h"

/*****************************************************/
// standaard constructor + destructor
FuzzyVariable::FuzzyVariable() 
{
	//standaard waarden toekennen aan start en end variabelen.
	// dit geeft  y = 0 * x + 0 -> horizontale lijn over y = 0
	startA = 0;
	startB = 0;
	
	// dit geeft  y = 0 * x + 1 -> horizontale lijn over y = 1
	endA = 0;
	endB = 1;
}
FuzzyVariable::~FuzzyVariable()
{

}


FuzzyVariable::FuzzyVariable(double start_a, double start_b, double end_a, double end_b)
{
	// waarden toekennen aan start en end waarde
	startA = start_a;
	startB = start_b;
	
	endA = end_a;
	endB = end_b;
}


/*****************************************************/
// functies
double FuzzyVariable::Fuzzify(double x)
{
	// maken van fuzzy waarde van y
	double y = startA * x + startB;
	if (y >= 1)
	{
		y = endA * x + endB;
	}
	if (y <= 0)
	{
		y = 0;
	}

	return y;
}


vector<double> FuzzyVariable::DeFuzzify(double y)
{
	double x;
	// maken van vaste waarde voor x van fuzzy waarde y
	double x1 = (y - this->startB) / this->startA;
	double x2 = (y - this->endB) / this->endA;

	/*
	if (x1 < 0)
	{
		x = x2;
	}
	else
	{
		x = x1;
	}*/

	return vector<double>{ x1, x2 };
}














