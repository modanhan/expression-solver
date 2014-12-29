#include <iostream>
#include <vector>
#include <string>
#include <complex>

#include "parser.h"
#include "evaluator.h"

using namespace std;

int main(){
	string s;
	getline(cin,s);
	vector<string> v = expression_solver::parse(s);
	complex<double> c = expression_solver::evaluate(v);
	cout << c << "\n";
	return 0;
}