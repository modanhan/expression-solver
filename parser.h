#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
namespace expression_solver{
	std::vector<std::string> parse(std::string s);
	void debug(bool b);
}
#endif