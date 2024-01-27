#ifndef STATMET_H
#define STATMET_H

#include <string>
#include <vector>

struct Statment{
	virtual std::string getContent(const std::string& local_time) = 0;
	virtual std::string getLocalTime() = 0;
	virtual ~Statment();

	std::vector<Statment*> inner_statments;
};

#endif