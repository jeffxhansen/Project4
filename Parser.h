#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include "Token.h"

using namespace std;


class Parser {
private:
	vector<Token*> tokens;

public:
	Parser(vector<Token*> inputTokens) {
		tokens = inputTokens;
	}
	
	void parse() {
		// try
		try {
			for (unsigned int i = 0; i < tokens.size(); i++) {
				datalogProgram(i);
			}
			cout << "Success!" << endl;
		}
		catch (Token* thrownToken) {
			cout << "Failure!" << endl;
			cout << "  " << thrownToken->toString() << endl;
		}
			// for loop for tokens.size();
				// Token currentToken;
				/*datalogProgram->SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF

				schemeList->scheme schemeList | lambda
				factList->fact factList | lambda
				ruleList->rule ruleList | lambda
				queryList->query queryList | lambda
	
				scheme->ID LEFT_PAREN ID idList RIGHT_PAREN
				fact->ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
				rule->headPredicate COLON_DASH predicate predicateList PERIOD
				query->predicate Q_MARK
	
				headPredicate->ID LEFT_PAREN ID idList RIGHT_PAREN
				predicate->ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	
				predicateList->COMMA predicate predicateList | lambda
				parameterList->COMMA parameter parameterList | lambda
				stringList->COMMA STRING stringList | lambda
				idList->COMMA ID idList | lambda
	
				parameter->STRING | ID | expression
				expression->LEFT_PAREN parameter operator parameter RIGHT_PAREN
				operator	->	ADD | MULTIPLY*/

			// print "Success!"
		// catch
			// print "Failure!"
	}

	bool matchesThrow(unsigned int& i, TokenType inputType);
	bool matches(unsigned int& i, TokenType inputType);

	void datalogProgram(unsigned int& i);

	void schemeList(unsigned int& i);
	void factList(unsigned int& i);
	void ruleList(unsigned int& i);
	void queryList(unsigned int& i);

	void scheme(unsigned int& i);
	void fact(unsigned int& i);
	void rule(unsigned int& i);
	void query(unsigned int& i);

	void headPredicate(unsigned int& i);
	void predicate(unsigned int& i);

	void predicateList(unsigned int& i);
	void parameterList(unsigned int& i);
	void stringList(unsigned int& i);
	void idList(unsigned int& i);

	void parameter(unsigned int& i);
	void expression(unsigned int& i);
	void parseOperator(unsigned int& i);
};

#endif // PARSER_H