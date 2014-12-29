#include <iostream>
#include <vector>
#include <string>

#include "parser.h"

using namespace std;

int main(){
	string s;
	getline(cin,s);
	vector<string> v = parser::parse(s);
	for (string a : v){
		cout << a << " ";
	}
	cout << "\n";
	return 0;
}