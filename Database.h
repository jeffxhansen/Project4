#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <map>

#include "Relation.h"

using namespace std;

class Database {
private:
	map<string, Relation> relations;

public:
	Database() {}

	void addRelation(Relation relation) {
		relations.insert(pair<string, Relation>(relation.getName(), relation));
	}

	map<string, Relation> getRelations() {
		return relations;
	}

	void addTuple(Tuple tuple, string name) {
		map<string, Relation>::iterator iter;
		for (iter = relations.begin(); iter != relations.end(); iter++) {
			if (iter->first == name) {
				iter->second.addTuple(tuple);
			}
		}
	}

	Relation* getRelation(string name) {
		map<string, Relation>::iterator iter;
		for (iter = relations.begin(); iter != relations.end(); iter++) {
			if (iter->first == name) {
				return iter->second;
			}
		}
		return &Relation();
	}

	string toString() {
		string str = "";

		map<string, Relation>::iterator iter;
		for (iter = relations.begin(); iter != relations.end(); iter++) {
			/*str += iter->second.getName();
			str += iter->second.headerToString();
			str += "\n";*/
			str += iter->second.toString();
			str += "\n";
		}

		return str;
	}

};


#endif // DATBASE_H
