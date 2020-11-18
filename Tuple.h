#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tuple {
private:
	vector<string> values;

public:
	Tuple(string str1 = "", string str2 = "", string str3 = "", string str4 = "", 
		string str5 = "", string str6 = "", string str7 = "") {
		values.push_back(str1);
		values.push_back(str2);
		values.push_back(str3);
		values.push_back(str4);
		values.push_back(str5);
		values.push_back(str6);
		values.push_back(str7);

		if (str7 == "") values.pop_back();
		if (str6 == "") values.pop_back();
		if (str5 == "") values.pop_back();
		if (str4 == "") values.pop_back();
		if (str3 == "") values.pop_back();
		if (str2 == "") values.pop_back();
		if (str1 == "") values.pop_back();
	}

	void addVal(string val) {
		values.push_back(val);
	}

	int size() {
		return values.size();
	}

	void clear() {
		values.clear();
	}

	vector<string> getValues() const {
		return values;
	}

	string at(unsigned int index) {
		if (index < values.size()) return values.at(index);
		else return "ACCESSED TUPLE OUT OF RANGE";
	}

	string toString() { // FIXME: As written is just for testing
		string str = "";
		for (unsigned int i = 0; i < values.size(); i++) {
			str += values.at(i);
			str += " ";
		}
		return str;
	}

	bool operator< (const Tuple& other) const {
		if (values.size() != other.getValues().size()) {
			cout << "Error comparing tuples of different size!" << endl;
			return false;
		}

		for (unsigned int i = 0; i < values.size(); i++) {
			if (other.getValues().at(i) < values.at(i)) {
				return false;
			}
			if (values.at(i) < other.getValues().at(i)) {
				return true;
			}

		}
		return false;
	}
};


#endif // TUPLE_H
