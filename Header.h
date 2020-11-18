#ifndef HEADER_H
#define HEADER_H

#define ERROR -1

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Header {
private:
	vector<string> attributes;

public:
	Header(string str1 = "", string str2 = "", string str3 = "", string str4 = "", 
		string str5 = "", string str6 = "", string str7 = "") {
		attributes.push_back(str1);
		attributes.push_back(str2);
		attributes.push_back(str3);
		attributes.push_back(str4);
		attributes.push_back(str5);
		attributes.push_back(str6);
		attributes.push_back(str7);

		if (str7 == "") attributes.pop_back();
		if (str6 == "") attributes.pop_back();
		if (str5 == "") attributes.pop_back();
		if (str4 == "") attributes.pop_back();
		if (str3 == "") attributes.pop_back();
		if (str2 == "") attributes.pop_back();
		if (str1 == "") attributes.pop_back();
	}

	void addVal(string val) {
		attributes.push_back(val);
	}

	void removeVal() {
		attributes.pop_back();
	}

	int size() {
		return attributes.size();
	}

	string at(unsigned int index) {
		if (index < attributes.size()) return attributes.at(index);
		else return "ACCESSED ATTRIBUTE OUT OF RANGE";
	}

	int getColumnIndex(string input) {
		for (unsigned int i = 0; i < attributes.size(); i++) {
			if (attributes.at(i) == input) return i;
		}
		return ERROR;
	}

	void clear() {
		attributes.clear();
	}

	string toString() {
		/*
		// this is my previous version
		string str = "";
		for (unsigned int i = 0; i < attributes.size(); i++) {
			str += attributes.at(i);
			str += "\t";
		}
		return str;
		*/
		string str = "";
		for (unsigned int i = 0; i < attributes.size(); i++) {
			if (i == 0) str += "(";
			str += attributes.at(i);
			if (i == attributes.size() - 1) str += ")";
			else str += ",";
		}
		return str;
	}

};


#endif // HEADER_H
