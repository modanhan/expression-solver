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
			if (argv[i][0] == '-' && sizeof(argv[i]) > 1){
				switch (argv[i][1]){
				case 'd':
					expression_solver::debug(true);
					cout << "Debug mode enabled\n";
					break;
				case '-':
					if (!strcmp(argv[i],"--help")){
						cout << "Expression Solver\n\n\
\tSolves mathematical expressions.\n\
\tSupported operators include: ( ) ^ * / + -\n\
\t- operator can also be used to negate values.\n\
\tSupported constants include: i\n\
\ti represents 1 imaginary unit.\n\n\
Known issues:\n\
\tLimited precision\n\n\
Input:\tAny correct mathematical expression.\n\
\tEnter exit to quit the program.\n\
Output:\t(x, y) where x is the real part of the evaluated expression, \
and y is the imaginary part.\n\n\
Examples:\n\
\tInput: 1+2\t\t\tOutput: (3,0)\n\
\tInput: -1.2i+i+1\t\tOutput: (1,-0.2)\n\
\tInput: -(-(-1.5)*2^(-1+4))\tOutput: (-12,0)\n";
						return 0;
					}
					else{
						cout << "Unknown option: " << argv[i] << "\nUsage: " << argv[0] << " [-option]\n";
						cout << "Enter " << argv[0] << " --help for help.\n";
						return 0;
					}
				default:
					cout << "Unknown option: " << argv[i] << "\n";
					cout << "Enter " << argv[0] << " --help for help.\n";
					return 0;
				}
			}
			else{
				cout << "Unknown option: " << argv[i] << "\nUsage: " << argv[0] << " [-option]\n";
				cout << "Enter " << argv[0] << " --help for help.\n";
				return 0;
			}
		}
	}
	string s;
	while (getline(cin, s)){
		if (s == "exit"){
			return 0;
		}
		vector<string> v = expression_solver::parse(s);
		complex<double> c = expression_solver::evaluate(v);
		cout << c << "\n";
	}
	return 0;
}