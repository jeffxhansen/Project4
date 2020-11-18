#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"
#include "Token.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Predicate {
private:
	string id;
	vector<Parameter*> parameters;
	TokenType type;

public:
	Predicate() {
		id = "";
		type = UNDEFINED;
	}

	Predicate(string inputID, TokenType inputType, string par1 = "", string par2 = "",
		string par3 = "", string par4 = "") {

		this->type = inputType;
		this->id = inputID;
		if (par1 != "") {
			parameters.push_back(new Parameter(par1));
		}

		if (par2 != "") {
			parameters.push_back(new Parameter(par2));
		}

		if (par3 != "") {
			parameters.push_back(new Parameter(par3));
		}

		if (par4 != "") {
			parameters.push_back(new Parameter(par4));
		}
		
	}

	void setID(string inputID) {
		this->id = inputID;
	}

	void setType(TokenType inputType) {
		this->type = inputType;
	}

	void setParameter(string par) {
		parameters.push_back(new Parameter(par));
	}

	void clear() {
		id = "";
		type = UNDEFINED;
		parameters.clear();

	}

	string getID() {
		return id;
	}

	TokenType getType() {
		return this->type;
	}

	string getParameter(unsigned int i) {
		return parameters.at(i)->toString();
	}

	vector<Parameter*> getParameters() {
		return parameters;
	}

	unsigned int size() {
		return parameters.size();
	}

	string toString() {
		string finalString = "";
		
		finalString += id;
		finalString += "(";
		for (unsigned int i = 0; i < parameters.size(); i++) {
			if (parameters.at(i)->isConstant()) {
				finalString += "\'";
				finalString += parameters.at(i)->toString();
				finalString += "\'";
			}
			else {
				finalString += parameters.at(i)->toString();
			}
			
			if (i != (parameters.size() - 1)) {
				finalString += ",";
			}
		}
		finalString += ")";

		if (this->type == FACTS) finalString += ".";
		if (this->type == QUERIES) finalString += "?";

		return finalString;
	}


};
#endif // PREDICATE_H
