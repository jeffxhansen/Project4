#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <string>
#include <stack>

#include "Token.h"

using namespace std;

class Parameter {
private:
	bool constant;
	string value;
	string expression;

public:
	Parameter() {
		constant = false;
		value = "";
		expression = "";
	}
	Parameter(string input) {
		value = input;
		if (input.at(0) == '\'') {
			constant = true;
			value = reformat(value);
		}
		else constant = false;
		expression = "";
	}

	string reformat(string input) {
		string returnString = "";
		for (unsigned int i = 0; i < input.size(); i++) {
			if (i != 0 && i != (input.size() - 1)) {
				returnString += input.at(i);
			}
		}
		return returnString;
	}

	void set(string input) {
		this->value = input;
		if (input.at(0) == '\'') {
			constant = true;
			value = reformat(value);
		}
		else constant = false;
		return;
	}

	void clear() {
		value = "";
		expression = "";
	}

	void buildExpression(string input) {
		expression += input;
		return;
	}

	bool isBalanced() {
		stack<char> parStack;
		int numOpen = 0;
		int numClose = 0;
		for (unsigned int i = 0; i < expression.size(); i++) {
			if (expression.at(i) == '(') {
				parStack.push(expression.at(i));
				numOpen++;
			}
			if (expression.at(i) == ')') {
				parStack.push(expression.at(i));
				numClose++;
			}
		}

		if ((parStack.size() % 2 == 0) && (numOpen == numClose)) {
			return true;
		}
		else return false;
	}

	bool isConstant() {
		return constant;
	}

	string expressionString() {
		return expression;
	}

	string toString() {
		return value;
	}

};

#endif // PARAMETER_H