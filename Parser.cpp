#include "Parser.h"

using namespace std;

#define Schemes
#define Facts
#define Rules
#define Queries

void Parser::datalogProgram(unsigned int& i) {
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

void Parser::schemeList(unsigned int& i) {
	// schemeList->scheme schemeList | lambda
	if (matches(i, FACTS)) return;
	scheme(i);
	schemeList(i);
	// cout << "schemeList" << endl;
	return;
}
void Parser::scheme(unsigned int& i) {
	// scheme->ID LEFT_PAREN ID idList RIGHT_PAREN

	matchesThrow(i, ID);
	matchesThrow(i, LEFT_PAREN);
	matchesThrow(i, ID);
	idList(i);
	matchesThrow(i, RIGHT_PAREN);
	// cout << "scheme" << endl;
	return;
}
void Parser::idList(unsigned int& i) {
	// idList->COMMA ID idList | lambda

	if (matches(i, RIGHT_PAREN)) return;

	matchesThrow(i, COMMA);
	matchesThrow(i, ID);
	idList(i);
	// cout << "idList" << endl;
	return;
}

void Parser::factList(unsigned int& i) {
	// factList->fact factList | lambda
	if (matches(i, RULES)) return;
	fact(i);
	factList(i);
	// cout << "factList" << endl;
	return;
}

void Parser::fact(unsigned int& i) {
	// fact->ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	matchesThrow(i, ID);
	matchesThrow(i, LEFT_PAREN);
	matchesThrow(i, STRING);
	stringList(i);
	matchesThrow(i, RIGHT_PAREN);
	matchesThrow(i, PERIOD);
	// cout << "fact" << endl;
	return;
}

void Parser::stringList(unsigned int& i) {
	// stringList->COMMA STRING stringList | lambda
	if (matches(i, RIGHT_PAREN)) return;
	matchesThrow(i, COMMA);
	matchesThrow(i, STRING);
	stringList(i);
	// cout << "stringList" << endl;
	return;
}

void Parser::ruleList(unsigned int& i) {
	// ruleList->rule ruleList | lambda
	if (matches(i, QUERIES)) return;
	rule(i);
	ruleList(i);
	// cout << "ruleList" << endl;
	return;
}

void Parser::rule(unsigned int& i) {
	// rule->headPredicate COLON_DASH predicate predicateList PERIOD
	headPredicate(i);
	matchesThrow(i, COLON_DASH);
	predicate(i);
	predicateList(i);
	matchesThrow(i, PERIOD);
	// cout << "rule" << endl;
	return;
}

void Parser::headPredicate(unsigned int& i) {
	// headPredicate->ID LEFT_PAREN ID idList RIGHT_PAREN
	matchesThrow(i, ID);
	matchesThrow(i, LEFT_PAREN);
	matchesThrow(i, ID);
	idList(i);
	matchesThrow(i, RIGHT_PAREN);
	// cout << "headPredicate" << endl;
	return;
}

void Parser::predicate(unsigned int& i) {
	// predicate->ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	matchesThrow(i, ID);
	matchesThrow(i, LEFT_PAREN);
	parameter(i);
	parameterList(i);
	matchesThrow(i, RIGHT_PAREN);
	// cout << "predicate" << endl;
	return;
}

void Parser::predicateList(unsigned int& i) {
	// predicateList->COMMA predicate predicateList | lambda
	if (matches(i, PERIOD)) return;
	matchesThrow(i, COMMA);
	predicate(i);
	predicateList(i);
	// cout << "predicateList" << endl;
	return;
}

void Parser::parameterList(unsigned int& i) {
	// parameterList->COMMA parameter parameterList | lambda
	if (matches(i, RIGHT_PAREN)) return;
	matchesThrow(i, COMMA);
	parameter(i);
	parameterList(i);
	// cout << "parameterList" << endl;
	return;
}

void Parser::parameter(unsigned int& i) {
	// parameter->STRING | ID | expression
	if (matches(i, STRING)) matchesThrow(i, STRING);
	if (matches(i, ID)) matchesThrow(i, ID);
	if (matches(i, LEFT_PAREN)) expression(i);
	// cout << "parameter" << endl;
	return;
}

void Parser::queryList(unsigned int& i) {
	// queryList->query queryList | lambda
	if (matches(i, E_O_F)) return;
	query(i);
	queryList(i);
	return;
}

void Parser::query(unsigned int& i) {
	// query->predicate Q_MARK
	predicate(i);
	matchesThrow(i, Q_MARK);
	return;
}

void Parser::expression(unsigned int& i) {
	// expression->LEFT_PAREN parameter operator parameter RIGHT_PAREN
	matchesThrow(i, LEFT_PAREN);
	parameter(i);
	parseOperator(i);
	parameter(i);
	matchesThrow(i, RIGHT_PAREN);
	return;
}

void Parser::parseOperator(unsigned int& i) {
	// operator	->	ADD | MULTIPLY
	if (matches(i, ADD)) matchesThrow(i, ADD);
	else if (matches(i, MULTIPLY)) matchesThrow(i, MULTIPLY);
	else throw tokens.at(i);
	return;
}

bool Parser::matches(unsigned int& i, TokenType inputType) {
	
	if (tokens.at(i)->type() == inputType) {
		//// cout << tokens.at(i)->typeString() << endl;
		return true;
	}
	else {
		return false;
	}
}

bool Parser::matchesThrow(unsigned int& i, TokenType inputType) {

	if (tokens.at(i)->type() == inputType) {
		// cout << tokens.at(i)->typeString() << endl;
		i++;
		return true;
	}
	else if (matches(i, COMMENT)) {
		do {
			// cout << tokens.at(i)->typeString() << endl;
			i++;
		} while (matches(i, COMMENT));

		if (!matches(i, E_O_F)) i++;

		return true;
	}
	else {
		throw tokens.at(i);
		return false;
	}
}