#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>

#include "Database.h"
#include "DatalogProgram.h"

using namespace std;

class Interpreter {
private:
	Database database;
	DatalogProgram datalog;

public:
	Interpreter(DatalogProgram datalog) {
		this->datalog = datalog;
	}

	void interpret() {
		interpretSchemes();
		interpretFacts();
		evaluateRules();
		//interpretQueries();
	}

	void interpretSchemes() {
		Relation relation;
		vector<Predicate> schemes = datalog.getSchemes();

		for (unsigned int i = 0; i < datalog.getSchemes().size(); i++) {
			Predicate predicate = schemes.at(i);
			Header header;

			relation.setName(predicate.getID());

			for (unsigned int k = 0; k < predicate.size(); k++) {
				header.addVal(predicate.getParameter(k));
			}
			relation.setHeader(header);

			database.addRelation(relation);
			relation.clear();
			header.clear();
		}
	}

	void interpretFacts() {
		vector<Predicate> facts = datalog.getFacts();

		for (unsigned int i = 0; i < facts.size(); i++) {
			Predicate fact = facts.at(i);
			string name = fact.getID();

			Tuple tuple;

			for (unsigned int k = 0; k < fact.size(); k++) {
				tuple.addVal(fact.getParameter(k));
			}

			database.addTuple(tuple, name);

			tuple.clear();
			fact.clear();
			name = "";
		}
	}

	void interpretQueries() {
		vector<Predicate> queries = datalog.getQueries();
		Predicate predicate;
		Relation relation;

		for (unsigned int i = 0; i < queries.size(); i++) {
			predicate = queries.at(i);
			relation = evaluatePredicate(predicate);

			cout << queries.at(i).toString() << " ";
			if (relation.size() == 0) cout << "No" << endl;
			else {
				cout << "Yes(" << relation.size() << ")" << endl;
				if (relation.toString() != "  \n") cout << relation.toString();
			}
		}
		
	}

	//fixed point algorithm
	void evaluateRules() {
		//EvalutatPredicate (like with queries)
			// Relation
		//Join
		//Project
		//Rename
		//Union
	}

	void evaluateRule() {

	}

	Relation* join(Relation& r1, Relation& r2) {
		//header = combineHeaders()
		//Relation relation = new Relation(header)
		//for each tuple t1 in r1
			//for each tuple t2 in r2

				//isJoinable(t1, t2)
					//Tuple t = join(t1, t2)
					//realtion.addTuple(t)
				//
			//
		//
		return &r1;
	}

	Header combineHeaders() {

	}

	bool isJoinable(Tuple t1, Tuple t2) {

	}

	Tuple combineTuples(Tuple t1, Tuple t2 /*information where they should match*/) {

	}

	void unionify() {

	}

	Relation evaluatePredicate(Predicate predicate) {
		string name = predicate.getID();
		Relation relation = database.getRelation(name);

		vector<Parameter*> parameters = predicate.getParameters();

		map<string, int> variables;

		vector<string> names;
		vector<int> columns;

		//relation = relation.selectColVal(0, "a");

		for (unsigned int i = 0; i < parameters.size(); i++) {
			if (parameters.at(i)->isConstant()) {
				//cout << i << " " << parameters.at(i)->toString() << "<----" << endl;
				relation = relation.selectColVal(i, parameters.at(i)->toString());
			}
			else {
				if (variables.find(parameters.at(i)->toString()) == variables.end()) {
					variables.insert({ parameters.at(i)->toString() , i });
					names.push_back(parameters.at(i)->toString());
					columns.push_back(i);
				}
				else {
					int firstOccurence = variables.find(parameters.at(i)->toString())->second;
					relation = relation.selectColCol(firstOccurence, i);
				}
			}
		}

		relation = relation.project(columns);
		relation = relation.rename(names);

		return relation;
	}

	

	void test() {
		cout << database.toString() << endl;
		cout << "\t-----" << endl << endl;

		Relation* r1 = database.getRelation("f");
		Relation* r2 = database.getRelation("r");

		Relation* joined = join(*r1, *r2);

		cout << r1->toString() << endl;
		cout << r2->toString() << endl;
		cout << "Join r1 and r2" << endl;
		cout << joined->toString();



	}

};


#endif // TUPLE_H
