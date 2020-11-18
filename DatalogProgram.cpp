#include "DatalogProgram.h"

using namespace std;

#define Schemes
#define Facts
#define Rules
#define Queries

void DatalogProgram::parser(unsigned int& i) {
	// datalogProgram->SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF

#ifdef Schemes
	matchesThrow(i, SCHEMES);
	matchesThrow(i, COLON);

	scheme(i);
	schemeList(i);
#endif // Schemes

#ifdef Facts
	matchesThrow(i, FACTS);
	matchesThrow(i, COLON);

	factList(i);

	matchesThrow(i, RULES);
	matchesThrow(i, COLON);
#endif //Facts

#ifdef Rules
	ruleList(i);

	matchesThrow(i, QUERIES);
	matchesThrow(i, COLON);
#endif // Rules

#ifdef Queries
	query(i);
	queryList(i);
#endif // Queries

	matchesThrow(i, E_O_F);

	return;
}

void DatalogProgram::schemeList(unsigned int& i) {
	// schemeList->scheme schemeList | lambda
	if (matches(i, FACTS)) return;
	scheme(i);
	schemeList(i);
	// cout << "schemeList" << endl;
	return;
}
void DatalogProgram::scheme(unsigned int& i) {
	// scheme->ID LEFT_PAREN ID idList RIGHT_PAREN
	temp.setType(SCHEMES);

	temp.setID(matchesThrow(i, ID));
	matchesThrow(i, LEFT_PAREN);
	temp.setParameter(matchesThrow(i, ID));
	idList(i);
	matchesThrow(i, RIGHT_PAREN);
	// cout << "scheme" << endl;

	schemes.push_back(temp);
	temp.clear();
	return;
}
void DatalogProgram::idList(unsigned int& i) {
	// idList->COMMA ID idList | lambda
	if (currType != RULES) {
		if (matches(i, RIGHT_PAREN)) return;

		matchesThrow(i, COMMA);
		temp.setParameter(matchesThrow(i, ID));
		idList(i);
		// cout << "idList" << endl;
		return;
	}
	else {
		if (isHead) {
			if (matches(i, RIGHT_PAREN)) return;

			matchesThrow(i, COMMA);
			tempRule.setHeadParameter(matchesThrow(i, ID));
			idList(i);
			// cout << "idList" << endl;
			return;
		}
		else {
			if (matches(i, RIGHT_PAREN)) return;

			matchesThrow(i, COMMA);
			temp.setParameter(matchesThrow(i, ID));
			idList(i);
			// cout << "idList" << endl;
			return;
		}

	}

}

void DatalogProgram::factList(unsigned int& i) {
	// factList->fact factList | lambda
	if (matches(i, RULES)) return;
	fact(i);
	factList(i);
	// cout << "factList" << endl;
	return;
}

void DatalogProgram::fact(unsigned int& i) {
	// fact->ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	temp.setType(FACTS);
	temp.setID(matchesThrow(i, ID));
	matchesThrow(i, LEFT_PAREN);
	temp.setParameter(matchesThrow(i, STRING));
	stringList(i);
	matchesThrow(i, RIGHT_PAREN);
	matchesThrow(i, PERIOD);
	// cout << "fact" << endl;

	facts.push_back(temp);
	temp.clear();
	return;
}

void DatalogProgram::stringList(unsigned int& i) {
	// stringList->COMMA STRING stringList | lambda
	if (matches(i, RIGHT_PAREN)) return;
	matchesThrow(i, COMMA);
	temp.setParameter(matchesThrow(i, STRING));
	stringList(i);
	// cout << "stringList" << endl;
	return;
}

void DatalogProgram::ruleList(unsigned int& i) {
	// ruleList->rule ruleList | lambda
	if (matches(i, QUERIES)) return;
	rule(i);
	ruleList(i);
	// cout << "ruleList" << endl;
	return;
}

void DatalogProgram::rule(unsigned int& i) {
	// rule->headPredicate COLON_DASH predicate predicateList PERIOD
	temp.setType(RULES);
	currType = RULES;
	isHead = true;
	isExpression = false;
	headPredicate(i);
	matchesThrow(i, COLON_DASH);
	predicate(i);
	predicateList(i);
	matchesThrow(i, PERIOD);
	// cout << "rule" << endl;
	tempRule.addBodyPredicate(temp);
	rules.push_back(tempRule);
	tempRule.clear();
	temp.clear();
	//tempRule.clear();
	return;
}

void DatalogProgram::headPredicate(unsigned int& i) {
	// headPredicate->ID LEFT_PAREN ID idList RIGHT_PAREN
	tempRule.setHeadID(matchesThrow(i, ID));
	matchesThrow(i, LEFT_PAREN);
	tempRule.setHeadParameter(matchesThrow(i, ID));
	idList(i);
	matchesThrow(i, RIGHT_PAREN);
	// cout << "headPredicate" << endl;
	isHead = false;
	return;
}

void DatalogProgram::predicate(unsigned int& i) {
	// predicate->ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	if (currType == QUERIES) {
		temp.setID(matchesThrow(i, ID));
		matchesThrow(i, LEFT_PAREN);
		parameter(i);
		parameterList(i);
		//temp.setParameter(tempExp.expressionString());
		matchesThrow(i, RIGHT_PAREN);
		// cout << "predicate" << endl;
		return;
	}
	else if (currType == RULES) {
		temp.setID(matchesThrow(i, ID));
		matchesThrow(i, LEFT_PAREN);
		parameter(i);
		parameterList(i);
		//temp.setParameter(tempExp.expressionString());
		matchesThrow(i, RIGHT_PAREN);
		// cout << "predicate" << endl;
		tempRule.addBodyPredicate(temp);
		temp.clear();
		return;
	}

}

void DatalogProgram::predicateList(unsigned int& i) {
	// predicateList->COMMA predicate predicateList | lambda
	if (matches(i, PERIOD)) return;
	matchesThrow(i, COMMA);
	predicate(i);
	predicateList(i);
	// cout << "predicateList" << endl;
	return;
}

void DatalogProgram::parameterList(unsigned int& i) {
	// parameterList->COMMA parameter parameterList | lambda
	if (matches(i, RIGHT_PAREN)) return;
	matchesThrow(i, COMMA);
	parameter(i);
	parameterList(i);
	// cout << "parameterList" << endl;
	return;
}

void DatalogProgram::parameter(unsigned int& i) {
	// parameter->STRING | ID | expression
	if (matches(i, STRING)) {
		if (isExpression) {
			tempExp.buildExpression(matchesThrow(i, STRING));
		}
		else {
			temp.setParameter(matchesThrow(i, STRING));
		}
	}
	if (matches(i, ID)) {
		if (isExpression) {
			tempExp.buildExpression(matchesThrow(i, ID));
		}
		else {
			temp.setParameter(matchesThrow(i, ID));
		}
	}

	if (matches(i, LEFT_PAREN)) {
		isExpression = true;
		expression2(i);
		if (!isExpression) {
			temp.setParameter(tempExp.expressionString());
		}
		//temp.setParameter(tempExp.expressionString());
	}

	/*if (matches(i, LEFT_PAREN)) {
		isExpression = true;
		expression(i);
	}
	isExpression = false;*/

	// cout << "parameter" << endl;
	return;
}

void DatalogProgram::expression2(unsigned int& i) {
	if (isExpression) {
		tempExp.buildExpression(matchesThrow(i, LEFT_PAREN));
		parameter(i);
		parseOperator(i);
		parameter(i);
		tempExp.buildExpression(matchesThrow(i, RIGHT_PAREN));
		if (tempExp.isBalanced()) isExpression = false;
		return;
	}
	else {
		matchesThrow(i, LEFT_PAREN);
		parameter(i);
		parseOperator(i);
		parameter(i);
		matchesThrow(i, RIGHT_PAREN);
		return;
	}
}

void DatalogProgram::queryList(unsigned int& i) {
	// queryList->query queryList | lambda
	if (matches(i, E_O_F)) return;
	query(i);
	queryList(i);
	return;
}

void DatalogProgram::query(unsigned int& i) {
	// query->predicate Q_MARK
	temp.setType(QUERIES);
	currType = QUERIES;
	isExpression = false;
	tempExp.clear();
	predicate(i);
	matchesThrow(i, Q_MARK);

	queries.push_back(temp);
	temp.clear();
	return;
}

void DatalogProgram::expression(unsigned int& i) {
	// expression->LEFT_PAREN parameter operator parameter RIGHT_PAREN
	if (isExpression) {
		tempExp.buildExpression(matchesThrow(i, LEFT_PAREN));
		parameter(i);
		parseOperator(i);
		parameter(i);
		tempExp.buildExpression(matchesThrow(i, RIGHT_PAREN));
		isExpression = false;
		temp.setParameter(tempExp.expressionString());
		return;
	}
	else {
		matchesThrow(i, LEFT_PAREN);
		parameter(i);
		parseOperator(i);
		parameter(i);
		matchesThrow(i, RIGHT_PAREN);
		isExpression = false;
		temp.setParameter(tempExp.expressionString());
		return;
	}

}

void DatalogProgram::parseOperator(unsigned int& i) {
	// operator	->	ADD | MULTIPLY
	if (matches(i, ADD)) {
		tempExp.buildExpression(matchesThrow(i, ADD));
	}
	else if (matches(i, MULTIPLY)) {
		tempExp.buildExpression(matchesThrow(i, MULTIPLY));
	}
	else throw tokens.at(i);
	return;
}

bool DatalogProgram::matches(unsigned int& i, TokenType inputType) {

	if (tokens.at(i)->type() == inputType) {
		//// cout << tokens.at(i)->typeString() << endl;
		return true;
	}
	else {
		return false;
	}
}

string DatalogProgram::matchesThrow(unsigned int& i, TokenType inputType) {

	if (tokens.at(i)->type() == inputType) {
		// cout << tokens.at(i)->typeString() << endl;
		i++;
		return tokens.at(i - 1)->getValue();
		/*if (!matches(i, E_O_F)) {
			return tokens.at(i)->getValue();
		}
		else {
			return "";
		}*/
	}
	else if (matches(i, COMMENT)) {
		do {
			// cout << tokens.at(i)->typeString() << endl;
			i++;
		} while (matches(i, COMMENT));

		if (!matches(i, E_O_F)) i++;

		return "";
	}
	else {
		throw tokens.at(i);
		return "";
	}
}