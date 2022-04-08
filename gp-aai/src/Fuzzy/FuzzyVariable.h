#pragma once
#include <vector>

using std::vector;

class FuzzyVariable 
{
private:
	double startA, startB;
	double endA, endB;

public:
	
		//standaard constructor + destructor
		FuzzyVariable();
		~FuzzyVariable();

		FuzzyVariable(double start_a, double start_b, double end_a, double endB);

		// functies
		double Fuzzify(double x);
		vector<double> DeFuzzify(double y);
};
