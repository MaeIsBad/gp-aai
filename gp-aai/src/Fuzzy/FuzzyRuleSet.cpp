#include <iostream>
#include "FuzzyRule.h"
#include "FuzzyVariable.h"
#include "FuzzyRuleSet.h"

using std::cout, std::endl;

/*****************************************************/
// standaard constructor + destructor
FuzzyRuleSet::FuzzyRuleSet()
{

}

FuzzyRuleSet::~FuzzyRuleSet()
{

}



/*****************************************************/
// functies
void FuzzyRuleSet::addFuzzyRule(FuzzyRule* fuzzyRule) {

	this->Rules.push_back(fuzzyRule);

}



vector<rulesetResult> FuzzyRuleSet::Calculate(double a, double b)
{
	vector<rulesetResult> result;

	for (auto rule : this->Rules) {
		cout << "Rule " << rule->getAntecedent1()->getName() << "(" << a << ", " << rule->getAntecedent1()->Fuzzify(a) << ")" << " and " 
			            << rule->getAntecedent2()->getName() << "(" << b << ", " << rule->getAntecedent2()->Fuzzify(b) << ")" << " = " 
			<< rule->Calculate(a, b) << " " << rule->getConcequent()->getName() << endl;
		
		result.push_back(rulesetResult {
			rule->Calculate(a, b),
			rule->getConcequent(),
			rule->getAntecedent1(),
			rule->getAntecedent2()
		});
	}
		

	return result;
}
