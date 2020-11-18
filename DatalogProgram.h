#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include <iostream>
#include <set>

#include "Token.h"
#include "Rule.h"
#include "Parameter.h"
#include "Predicate.h"

using namespace std;

class DatalogProgram {
private:
	vector<Token*> tokens;
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set <string> domain;

	Predicate temp;
	Parameter tempExp;
	Rule tempRule;

	TokenType currType;

	bool isHead;
	bool isExpression;

public:
	DatalogProgram() {
		isExpression = false;
		currType = UNDEFINED;
		isHead = false;
	}
	DatalogProgram(vector<Token*> inputTokens) {
		tokens = inputTokens;
		isExpression = false;
		currType = UNDEFINED;
		isHead = false;
	}

	vector<Token*> getTokens() { return tokens; }
	vector<Predicate> getSchemes() { return schemes; }
	vector<Predicate> getFacts() { return facts; }
	vector<Predicate> getQueries() { return queries; }
	vector<Rule> getRules() { return rules; }
	set <string> getDomain() { return domain; }
	
	void parse() {
		try {
			for (unsigned int i = 0; i < tokens.size(); i++) {
				parser(i);
			}
			//cout << "Success!" << endl;
			//print();
		}
		catch (Token* thrownToken) {
			//cout << "Failure!" << endl;
			//cout << "  " << thrownToken->toString() << endl;
		}
	}

	void print() {

		/*schemes.push_back(new Predicate("add", SCHEMES, "X", "Y", "Z"));
		schemes.push_back(new Predicate("nums", SCHEMES, "A", "B"));*/

		/*facts.push_back(Predicate("add", FACTS, "'1'", "'2'", "'3'"));
		facts.push_back(Predicate("add", FACTS, "'2'", "'4'", "'5'"));
		facts.push_back(Predicate("nums", FACTS, "'2'", "'3'"));
		facts.push_back(Predicate("nums", FACTS, "'6'", "'7'"));
		facts.push_back(Predicate("nums", FACTS, "'2'", "'6'"));*/

		/*queries.push_back(Predicate("add", QUERIES, "'2'", "'3'", "'5'"));
		queries.push_back(Predicate("add", QUERIES, "X", "Y", "'13'"));
		queries.push_back(Predicate("add", QUERIES, "X", "('3'*('4'+(X*'-1')))"));*/

		/*rules.push_back(Rule("HasSameAddress", RULES, "snap", RULES, "snap", RULES,
			"X", "Y", "", "",
			"A", "X", "B", "C",
			"D", "Y", "B", "E"));*/

		cout << "Schemes(" << schemes.size() << "):" << endl;
		for (unsigned int i = 0; i < schemes.size(); i++) {
			cout << "  " << schemes.at(i).toString() << endl;
		}

		cout << "Facts(" << facts.size() << "):" << endl;
		for (unsigned int i = 0; i < facts.size(); i++) {
			cout << "  " << facts.at(i).toString() << endl;
		}

		cout << "Rules(" << rules.size() << "):" << endl;
		for (unsigned int i = 0; i < rules.size(); i++) {
			cout << "  " << rules.at(i).toString() << endl;
		}

		cout << "Queries(" << queries.size() << "):" << endl;
		for (unsigned int i = 0; i < queries.size(); i++) {
			cout << "  " << queries.at(i).toString() << endl;
		}

		// populate set domain from facts
		for (unsigned int i = 0; i < facts.size(); i++) {
			for (unsigned int j = 0; j < facts.at(i).size(); j++) {
				domain.insert(facts.at(i).getParameter(j));
			}
		}

		cout << "Domain(" << domain.size() << "):" << endl;
		set <string> ::iterator itr;
		for (itr = domain.begin(); itr != domain.end(); itr++) {
			cout << "  " << *itr << endl;
		}
	}

	string toString() {
		string finalString;
		return finalString;
	}

	/* Input: test(((X+Y)*Z))?
	query
		predicate
			ID							(((X+Y)*Z))?
			LEFT_PAREN					 ((X+Y)*Z))?
			parameter
				expression
					LEFT_PAREN			  (X+Y)*Z))?
					parameter
						expression
							Left_PAREN
							ID
							+
							ID
							RIGHT_PAREN
					operator
						*
					parameter
						ID
					RIGHT_PAREN
				-addExpression
			paremeterList
				COMMA
				parameter
				paremeterList
			RIGHT_PRAEN
		Q_MARK
	queryList
	*/

	string matchesThrow(unsigned int& i, TokenType inputType);
	bool matches(unsigned int& i, TokenType inputType);

	void expression2(unsigned int& i);

	void parser(unsigned int& i);

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

#endif // DatalogProgram_H