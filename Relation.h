#ifndef RELATION_H
#define RELATION_H

#define PARAMETERS 7

#include <iostream>
#include <set>

#include "Header.h"
#include "Tuple.h"

using namespace std;

class Relation {
private:
	string name;
	
	Header header;
	set<Tuple> tuples;

public:
	Relation() {}
	Relation(string name, Header header, set<Tuple> tuples) {
		this->name = name;
		this->tuples = tuples;
		this->header = header;
	
	}

	Relation(string name, Header header) {
		this->name = name;
		this->header = header;
	}

	void addTuple(Tuple tuple) {
		tuples.insert(tuple);
	}

	void setName(string name) {
		this->name = name;
	}

	void setHeader(Header header) {
		this->header = header;
	}

	int width() {
		return header.size();
	}

	int size() {
		return tuples.size();
	}

	void clear() {
		name = "";
		header.clear();
		tuples.clear();
	}

	Relation rename(vector<string> names) {
		Relation newRelation(name, header, tuples);

		newRelation.header.clear();

		for (unsigned int i = 0; i < names.size(); i++) {
			if (names.at(i) != "") newRelation.header.addVal(names.at(i));
		}

		return newRelation;
	}

	Relation project(vector<int> indices) {
		Relation newRelation(name, header, tuples);

		newRelation.header.clear();
		newRelation.tuples.clear();

		for (unsigned int i = 0; i < indices.size(); i++) {
			if (indices.at(i) != -1) {
				newRelation.header.addVal(header.at(indices.at(i)));
			}
		}

		Tuple tempTuple;
		for (Tuple t : tuples) {
			for (unsigned int i = 0; i < indices.size(); i++) {
				if (indices.at(i) != -1) {
					tempTuple.addVal(t.at(indices.at(i)));
				}
			}
			newRelation.tuples.insert(tempTuple);
			tempTuple.clear();
		}

		return newRelation;
	}

	Relation selectColVal(int column, string value) {
		Relation newRelation(name, header, tuples);
		newRelation.tuples.clear();

		for (Tuple t : tuples) {
			if (t.at(column) == value) {
				newRelation.tuples.insert(t);
			}
		}

		return newRelation;
	}

	Relation selectColCol(int column1, int column2) {
		Relation newRelation(name, header, tuples);
		newRelation.tuples.clear();

		for (Tuple t : tuples) {
			if (t.at(column1) == t.at(column2)) {
				newRelation.tuples.insert(t);
			}
		}

		return newRelation;
	}

	string headerToString() {
		return header.toString();
	}

	string getName() {
		return name;
	}

	string toString() {
		string str = "";
		/*str += name;
		str += "\n";*/

		str += getName();
		str += headerToString();
		str += "\n";
		for (Tuple t : tuples) {
			str += "  ";
			for (int i = 0; i < header.size(); i++) {
				str += header.at(i);
				str += "=\'";

				str += t.at(i);
				str += "\'";
				if (i != header.size() - 1) str += ", ";
			}
			str += "\n";
		}

		return str;
	}

};


#endif // RELATION_H
