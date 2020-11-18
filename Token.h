#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum TokenType { COMMA = 0, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, 
	COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, 
	QUERIES, ID, STRING, COMMENT, UNDEFINED, E_O_F, COMMENT_BLOCK };

class Token {
	private:
		TokenType tokenType;
		string value;
		int lineNumber;
		
	public:
		Token() {
			value = "";
			lineNumber = 0;
			tokenType = UNDEFINED;
		}

		Token(TokenType inputType, string inputValue, int inputLineNumber) {
			tokenType = inputType;
			value = inputValue;
			lineNumber = inputLineNumber;
		}

		string tokenTypeToString(int type) {
			switch (type) {
			case COMMA:
				return "COMMA";
				break;
			case PERIOD:
				return "PERIOD";
				break;
			case Q_MARK:
				return "Q_MARK";
				break;
			case LEFT_PAREN:
				return "LEFT_PAREN";
				break;
			case RIGHT_PAREN:
				return "RIGHT_PAREN";
				break;
			case COLON:
				return "COLON";
				break;
			case COLON_DASH:
				return "COLON_DASH";
				break;
			case MULTIPLY:
				return "MULTIPLY";
				break;
			case ADD:
				return "ADD";
				break;
			case SCHEMES:
				return "SCHEMES";
				break;
			case FACTS:
				return "FACTS";
				break;
			case RULES:
				return "RULES";
				break;
			case ID:
				return "ID";
				break;
			case QUERIES:
				return "QUERIES";
				break;
			case STRING:
				return "STRING";
				break;
			case COMMENT:
				return "COMMENT";
				break;
			case UNDEFINED:
				return "UNDEFINED";
				break;
			case E_O_F:
				return "EOF";
				break;
			}
			return "";
		}

		string toString() {
			string finalToken = "";

			finalToken = "(" + tokenTypeToString(this->tokenType) + "," + 
				"\"" + value + "\"" + "," + 
				to_string(lineNumber) + ")";

			return finalToken;
		}

		void setValue(string input) {
			value = input;
			return;
		}

		void setLineNumber(int input) {
			lineNumber = input;
			return;
		}

		void setType(TokenType input) {
			tokenType = input;
			return;
		}

		string getValue() {
			return this->value;
		}

		int getLineNumber() {
			return this->lineNumber;
		}

		string typeString() {
			return tokenTypeToString(this->tokenType);
		}

		TokenType type() {
			return this->tokenType;
		}
};

#endif // TOKEN_H