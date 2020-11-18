#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>

#include "Token.h"
#include "Predicate.h"

using namespace std;

class Rule {
private:
	string value;
	Predicate headPredicate;
	vector<Predicate> bodyPredicates;

public:
	Rule() {
		setHeadType(RULES);
	}
	Rule(string inputID, TokenType inputType, 
		string inputID2, TokenType inputType2, 
		string inputID3, TokenType inputType3,
		string par1 = "", string par2 = "",
		string par3 = "", string par4 = "", 
		string par12 = "", string par22 = "",
		string par32 = "", string par42 = "", 
		string par13 = "", string par23 = "",
		string par33 = "", string par43 = "") {

		headPredicate.setID(inputID);
		headPredicate.setType(inputType);
		
		if (par1 != "") {
			headPredicate.setParameter(par1);
		}

		if (par2 != "") {
			headPredicate.setParameter(par2);
		}

		if (par3 != "") {
			headPredicate.setParameter(par3);
		}

		if (par4 != "") {
			headPredicate.setParameter(par4);
		}

		bodyPredicates.push_back(Predicate(inputID2, inputType2, 
			par12, par22, par32, par42));

		bodyPredicates.push_back(Predicate(inputID3, inputType3,
			par13, par23, par33, par43));


	}

	void setHeadID(string inputID) {
		headPredicate.setID(inputID);
	}

	void setHeadType(TokenType inputType) {
		headPredicate.setType(inputType);
	}

	void setHeadParameter(string par) {
		headPredicate.setParameter(par);
	}

	void addBodyPredicate(Predicate predicate) {
		bodyPredicates.push_back(predicate);
	}

	void clear() {
		value = "";
		headPredicate.clear();
		for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
			bodyPredicates.at(i).clear();
		}
		bodyPredicates.clear();

	}


	string toString() {
		value += headPredicate.toString();
		value += " :- ";
		bodyPredicates.pop_back();
		for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
			
			
			value += bodyPredicates.at(i).toString();
			if (i != (bodyPredicates.size() - 1)) {
				value += ",";
			}
		}
		value += ".";
		return value;
	}

};

#endif // RULE_H