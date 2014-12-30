#include <iostream>
#include "parser.h"


namespace expression_solver{
	using namespace std;
	string input;
	vector<string> processed;
	string ch;
	int position = 0;
	vector<string> output;

	bool debugon = false;

	void find();
	void expression();
	void term();
	void factor();
	void expterm();

	void debug(bool b){
		debugon = b;
	}

	void reset(){
		processed.clear();
		ch = "";
		position = 0;
		output.clear();
	}

	bool op(char c) {
		return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	}

	void process(){
		int bi = 0, ei = 0;
		while (bi < input.size()) {
			while (ei < input.size() && !op(input[ei])) {
				ei++;
			}
			if (bi != ei) {
				processed.push_back(input.substr(bi, ei - bi));
			}
			if ((input[ei] == '-') && (ei == 0 || op(input[ei - 1]))){
				processed.push_back("(");
				processed.push_back("0");
			}
			processed.push_back(input.substr(ei, 1));
			ei++;
			bi = ei;
		}
		if (debugon){
			for (string a : processed){
				cout << a << " ";
			}
			cout << "\n";
		}
	}

	void find() {
		if (position >= processed.size()){
			return;
		}
		ch = processed[position];
		position++;
	}

	void expression() {
		string op;
		term();
		while (ch == "+" || ch == "-") {
			op = ch;
			find();
			term();
			output.push_back(op);
		}
	}

	void term() {
		string op;
		expterm();
		while (ch == "*" || ch == "/") {
			op = ch;
			find();
			expterm();
			output.push_back(op);
		}
	}

	void expterm(){
		factor();
		while (ch == "^"){
			find();
			factor();
			output.push_back("^");
		}
	}

	void factor() {
		if (ch == "(") {
			find();
			expression();
		}
		else {
			output.push_back(ch);
		}
		find();
	}

	vector<string> parse(string s){
		reset();
		auto it = find(s.begin(), s.end(), ' ');
		while (it != s.end()){
			s.erase(it);
			it = find(it, s.end(), ' ');
		}
		input = s;
		process();
		find();
		do {
			expression();
		} while (position < processed.size() - 1);
		if (debugon)	{
			for (string a : output){
				cout << a << " ";
			}
			cout << "\n";
		}
		return output;
	}
}