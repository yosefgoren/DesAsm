#pragma once

#include <exception>
#include <string>

struct SemanticError : public std::exception{
	virtual std::string errorMsg() const = 0;
};

struct InternalError : public std::exception{
	InternalError(const std::string& msg);
	std::string msg;
};