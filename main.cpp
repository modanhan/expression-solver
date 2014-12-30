#include <iostream>
#include <vector>
#include <string>
#include <complex>

#include "parser.h"
#include "evaluator.h"

using namespace std;

int main(int argc, char *argv[]){
	if (argc != 1){
		for (int i = 1; i < argc; i++){
			if (argv[i][0] == '-'){
				switch (argv[i][1]){
				case 'd':
					expression_solver::debug(true);
					cout << "Debug mode enabled\n";
					break;
				default:
					cout << "Unknown option: -" << argv[i][1] << "\n";
					break;
				}
			}
			else{
				cout << "Unknown option: " << argv[i] << "\nUsage: " << argv[0] << " [-option]\n";
			}
		}
	}
	string s;
	while (getline(cin, s)){
		if (s == "q" || s == "exit"){
			return 0;
		}
		vector<string> v = expression_solver::parse(s);
		complex<double> c = expression_solver::evaluate(v);
		cout << c << "\n";
	}
	return 0;
}