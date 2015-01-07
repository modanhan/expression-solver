#include <iostream>
#include <stack>
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
		stack<int> ns;
		string num = "";
		for (int i = 0; i < input.size(); i++){
			if (op(input[i])){
				if (num != ""){
					processed.push_back(num);
					if (!ns.empty()){
						while (!ns.empty()){
							if (ns.top() == 0){
								processed.push_back(")");
								ns.pop();
								if (!ns.empty()){
									ns.top()--;
								}
							}
							else{
								break;
							}
						}
					}
				}
				bool neg = (input[i] == '-' && (i == 0 || (op(input[i - 1]) && input[i - 1] != ')')));
				if (!ns.empty()){
					if (input[i] == '('){
						ns.top()++;
					}
					else if (input[i] == ')'){
						ns.top()--;
					}
					if (neg){
						ns.top()++;
					}
					else{
						while (!ns.empty()){
							if (ns.top() == 0){
								processed.push_back(")");
								ns.pop();
								if (!ns.empty()){
									ns.top()--;
								}
							}
							else{
								break;
							}
						}
					}
				}
				if (neg){
					processed.push_back("(");
					processed.push_back("0");
					ns.push(0);
				}
				processed.push_back(input.substr(i, 1));
				num = "";
			}
			else{
				num += input[i];
			}
		}
		if (num != ""){
			processed.push_back(num);
		}
		while (!ns.empty()){
			if (ns.top() == 0){
				processed.push_back(")");
				ns.pop();
				if (!ns.empty()){
					ns.top()--;
				}
			}
			else{
				break;
			}
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