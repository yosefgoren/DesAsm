#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <vector>
#include "Statment.h"
#include "utility.h"

struct Exp : public Statment{
	Exp(int value);
	Exp();
	Exp(const std::string& func_name, const std::vector<Exp*> params);
	Exp(Statment* left_operand, Binop opeator, Statment* right_operand);

	virtual std::string getContent(const std::string& local_time);
	virtual std::string getLocalTime() = 0;

	std::vector<Statment*> inner_statments;
};

#endif