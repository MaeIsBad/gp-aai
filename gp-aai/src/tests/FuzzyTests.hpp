#include <cassert>
#include <iostream>
#include "Fuzzy/FuzzyVariable.h"
#include "Fuzzy/FuzzyRule.h"

using std::cout, std::endl;

void run_Fuzzy_tests() {


	//startA = (1.2/150);
	//startb = -0.2;

	//endA = -(1 / 150);
	//endB = 2;

	FuzzyVariable testMedium = FuzzyVariable(1.2 / 150, -0.2, -1.0 / 150.0, 2); // medium
	FuzzyVariable testAmmoStatOk = FuzzyVariable(0.1, 0, -0.5, 1.5);	//okay
	FuzzyVariable testdesireability = FuzzyVariable(0.02, -2, 0, 1);	// very

	auto defuzzy1 = testMedium.DeFuzzify(0.5);
	cout << defuzzy1[0] << "  " << defuzzy1[1] << endl;
	cout << testMedium.Fuzzify(100) << endl;

	cout << testMedium.Fuzzify(250) << endl;
	auto defuzzy2 = testMedium.DeFuzzify(0.7);
	cout << defuzzy2[0] << "  " << defuzzy2[1] << endl;


	FuzzyRule ruletest = FuzzyRule(testMedium, testAmmoStatOk, testdesireability, FuzzyOperator::AND);

	cout << ruletest.Calculate(100, 15) << endl;

}





