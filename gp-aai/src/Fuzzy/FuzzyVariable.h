#pragma once



class FuzzyVariable 
{
private:
	

public:
	double startA, startB;
	double endA, endB;

		//standaard constructor + destructor
		FuzzyVariable();
		~FuzzyVariable();

		// functies
		double Fuzzify(double x);
		double deFuzzify(double y);
};
