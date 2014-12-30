#include "parser.h"

namespace expression_solver{
	using namespace std;
	string input;
	vector<string> processed;
	string ch;
	int position = 0;
	vector<string> output;

	void find();
	void expression();
	void term();
	void factor();
	void expterm();

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
			if (ei == 0 || (input[ei] == '-'&&op(input[ei - 1]))){
				processed.push_back("0");
			}
			processed.push_back(input.substr(ei, 1));
			ei++;
			bi = ei;
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
		return output;
	}
}