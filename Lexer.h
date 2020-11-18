#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Lexer {
private:
	vector<Token*> tokens;
	ifstream in;
	int lineNumber;
	int newLines;
	char currentChar;
	string currentString;
	string input;
	bool continuation;
	TokenType continuationType;

public:
	Lexer() {
		lineNumber = 1;
		newLines = 0;
		currentChar = '\0';
		input = "";
		continuation = false;
	}
	Lexer(char* fileName) {
		in.open(fileName);
		lineNumber = 1;
		currentChar = '\0';
		input = "";
		continuation = false;
		if (!in) cout << "Error with reading file" << endl;
	}

	vector<Token*> Tokens() {
		return tokens;
	}

	void printTokens() {
		for (unsigned int i = 0; i < tokens.size(); i++) {
			cout << tokens.at(i)->toString() << endl;
		}
		cout << "Total Tokens = " << tokens.size() << endl;
	}

	void run() {
		 do {

			// cout << "currentString1: " << currentString << endl;
			currentString += currentChar;
			// cout << "currentString2: " << currentString << endl;

			if (!continuation) {
				
				switch (currentChar) {
				case(','):
					tokens.push_back(new Token(COMMA, ",", lineNumber));
					reset();
					break;
				case('.'):
					tokens.push_back(new Token(PERIOD, ".", lineNumber));
					reset();
					break;
				case('?'):
					tokens.push_back(new Token(Q_MARK, "?", lineNumber));
					reset();
					break;
				case('('):
					tokens.push_back(new Token(LEFT_PAREN, "(", lineNumber));
					reset();
					break;
				case(')'):
					tokens.push_back(new Token(RIGHT_PAREN, ")", lineNumber));
					reset();
					break;
				case('*'):
					tokens.push_back(new Token(MULTIPLY, "*", lineNumber));
					reset();
					break;
				case('+'):
					tokens.push_back(new Token(ADD, "+", lineNumber));
					reset();
					break;
				case(':'):
					if (in.peek() == '-') {
						// currentChar = in.get();
						// currentString = ":-";
						continuation = true;
						continuationType = COLON_DASH;
						currentString = ":";
						break;
					}
					else {
						tokens.push_back(new Token(COLON, ":", lineNumber));
						reset();
						break;
					}
				case('S'):
					continuation = true;
					continuationType = SCHEMES;
					currentString = "S";
					break;
				case('F'):
					// cout << "\tEntered case F" << endl;
					continuation = true;
					continuationType = FACTS;
					currentString = "F";
					break;
				case('R'):
					continuation = true;
					continuationType = RULES;
					currentString = "R";
					break;
				case('Q'):
					continuation = true;
					continuationType = QUERIES;
					currentString = "Q";
					break;
				case('#'):
					if (in.peek() == '|') {
						currentChar = in.get();
						continuation = true;
						continuationType = COMMENT_BLOCK;
						currentString = "#|";
					}
					else {
						continuation = true;
						continuationType = COMMENT;
						currentString = "#";
					}
					break;
				case('\''):
					continuation = true;
					continuationType = STRING;
					currentString = "\'";
					break;
				case(' '):
					currentString += currentChar;
					break;
				default:
					if (isalpha(currentChar)) {
						continuation = true;
						continuationType = ID;
						currentString = currentChar;
					}
					else if ((currentChar >= 0x00 && currentChar <= 0x1F) || currentChar >= 0x7F) {
						break;
					}
					else {
						currentString = currentChar;
						tokens.push_back(new Token(UNDEFINED, currentString, lineNumber));
						reset();
					}
					break;
				}
			}
			
			if(continuation) {

				switch (continuationType) {
				case(COLON_DASH):
					if (currentString == ":-") {
						tokens.push_back(new Token(COLON_DASH, ":-", lineNumber));
						reset();
						break;
					}
					break;
				case(SCHEMES):
					keyword("Schemes");
					break;
				case(FACTS):
					keyword("Facts");
					break;
				case(RULES):
					keyword("Rules");
					break;
				case(QUERIES):
					keyword("Queries");
					break;
				case(COMMENT):
					comment();
					break;
				case(COMMENT_BLOCK):
					commentBlock();
					break;
				case(STRING):
					processString();
					break;
				case(ID):
					processID();
					break;
				default:
					break;
				} // continuation switch statement
				
			} // !continuation
			
			if (in.peek() == '\n') {
				lineNumber++;
			}
			if (in.peek() == EOF) {
				tokens.push_back(new Token(E_O_F, "", lineNumber));
				break;
			}
		} while ((currentChar = in.get()));

		

	}

	void processID() {
		while (!terminatingChar2(in.peek())) {
			currentChar = in.get();
			currentString += currentChar;
		}
		
		tokens.push_back(new Token(ID, currentString, lineNumber));
		reset();
	}

	void processString() {

		bool goodString = false;

		/*do {
			currentChar = in.get();
			currentString += currentChar;
			if (currentChar == '\n') newLines++;
			if (currentChar == '\'') {
				if (in.peek() == '\'') {
					currentChar = in.get();
					currentString += currentChar;
					currentChar = in.get();
					currentString += currentChar;
					goodString = true;
					continue;
				}
				else {
					goodString = true;
					break;
				}
			}
			if (in.peek() == EOF) {
				goodString = false;
				break;
			}
		} while (currentChar != '\'' || goodString == true);*/

		do {
			currentChar = in.get();
			currentString += currentChar;

			if (currentChar == '\n') newLines++;

			if (currentChar == '\'') {
				if (in.peek() == '\'') {
					currentChar = in.get();
					currentString += currentChar;
					goodString = false;
				}
				else {
					goodString = true;
				}
			}

			if (in.peek() == EOF) {
				goodString = false;
				break;
			}
		} while (goodString == false);

		if (goodString == true) {
			tokens.push_back(new Token(STRING, currentString, lineNumber));
			reset();
		}
		else {
			tokens.push_back(new Token(UNDEFINED, currentString, lineNumber));
			reset();
		}
		
	}

	void commentBlock() {
		while (!endOfBlockComment(in.peek())) {
			//cout << "\tGot another char" << endl;
			currentChar = in.get();
			currentString += currentChar;

			if (currentChar == '\n') newLines++;
		}

		if (in.peek() == EOF) {
			tokens.push_back(new Token(UNDEFINED, currentString, lineNumber));
			reset();
		}
		else {
			//tokens.push_back(new Token(COMMENT, currentString, lineNumber));
			reset();
		}

		/*if (endOfBlockComment(in.peek())) {
		}*/
		return;
	}

	bool endOfBlockComment(char character) {
		if (character == EOF) {
			return true;
		}

		if (character == '|') {
			currentChar = in.get();
			currentString += currentChar;

			if (in.peek() == '#') {
				currentChar = in.get();
				currentString += currentChar;
				return true;
			}
			else return false;
		}
		else return false;

	}

	void comment() {

		while (!newLine(in.peek())) {
			//cout << "\tGot another char" << endl;
			currentChar = in.get();
			currentString += currentChar;
		}

		if (newLine(in.peek())) {
			//tokens.push_back(new Token(COMMENT, currentString, lineNumber));
			reset();
		}
		return;
	}

	void keyword(string toMatch) { // TASK: Implement keyword function
		string TO_MATCH = toMatch;
		TokenType type;

		//cout << "currentString1: " << currentString << endl;

		switch(TO_MATCH.at(0)) {
		case('S'):
			type = SCHEMES;
			break;
		case('F'):
			type = FACTS;
			break;
		case('R'):
			type = RULES;
			break;
		case('Q'):
			type = QUERIES;
			break;
		default:
			TO_MATCH = "";
			return;
		}

		while (!terminatingChar(in.peek())) {
			//cout << "\tGot another char" << endl;
			currentChar = in.get();
			currentString += currentChar;
		}

		//cout << "currentString2: " << currentString << endl;
		if (currentString == TO_MATCH) {
			//cout << "\tMade token: " << currentString << endl;
			tokens.push_back(new Token(type, currentString, lineNumber));
			reset();
		}
		else {
			//cout << "\tMade token: " << currentString << endl;
			tokens.push_back(new Token(ID, currentString, lineNumber));
			reset();
		}
	}

	bool newLine(char character) {
		if (character == '\n') {
			return true;
		}
		else if (character == EOF) {
			return true;
		}
		else return false;
	}

	bool normalChar(char character) {
		if (isalpha(character)) {
			return true;
		}
		
		return false;
	}

	bool terminatingChar2(char character) {
		if (character == '\n') {
			return true;
		}
		else if (character == ' ') {
			return true;
		}
		else if (character == EOF) {
			return true;
		}
		else if (!isalnum(character)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool terminatingChar(char character) {
		if (character == '\n') {
			return true;
		}
		else if (character == ' ') {
			return true;
		}
		else if (character == EOF) {
			return true;
		}
		else if (!isalpha(character)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool colon() {
		if (currentChar == ':') {
			if (in.peek() == '-') {
				currentChar = in.get();
				currentString += currentChar;
				tokens.push_back(new Token(COLON_DASH, currentString, lineNumber));
				reset();
			}
			else {
				tokens.push_back(new Token(COLON, ":", lineNumber));
				reset();
			}
			return true;
		}
		else {
			return false;
		}
	}

	bool singleChar() {
		switch (currentChar) {
		
		default:
			return false;
		}

		return true;
	}

	void updateLineNumber() {
		lineNumber += newLines;
	}

	void reset() {
		continuation = false;
		currentString = "";
		updateLineNumber();
		newLines = 0;
	}

	// Helper testing function
	void testInput() {
		do {
			if (currentChar == '\n') {
				cout << "_";
			}
			else if (currentChar == ' ') {
				cout << ".";
			}
			else {
				cout << currentChar;
			}
			if (in.peek() == EOF) {
				break;
			}
		} while ((currentChar = in.get()));
	}
};


#endif // LEXER2_H
