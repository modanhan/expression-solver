#include <stack>
#include "evaluator.h"

using namespace std;
typedef complex<double> cd;
namespace expression_solver{
	cd evaluate(vector<string> v){
		stack<cd> s;
		for (string a : v){
			if (*(a.end() - 1) == 'i'){
				if (a.size() == 1){
					cd c(0, 1);
					s.push(c);
				}
				else{
					double d = stod(a, NULL);
					cd c(0, d);
					s.push(c);
				}
			}
			else{
				switch (a[0]){
				case '+':{
					cd r = s.top();
					s.pop();
					cd l = s.top();
					s.pop();
					s.push(l + r);
					break; }
				case '-':{cd r = s.top();
					s.pop();
					cd l = s.top();
					s.pop();
					s.push(l - r);
					break; }
				case '*':{cd r = s.top();
					s.pop();
					cd l = s.top();
					s.pop();
					s.push(l * r);
					break; }
				case '/':{cd r = s.top();
					s.pop();
					cd l = s.top();
					s.pop();
					s.push(l / r);
					break; }
				case '^':{cd r = s.top();
					s.pop();
					cd l = s.top();
					s.pop();
					s.push(pow(l, r));
					break; }
				default:{
					double d = stod(a, NULL);
					cd c(d, 0);
					s.push(c);
					break; }
				}
			}
		}
		return s.top();
	}
}