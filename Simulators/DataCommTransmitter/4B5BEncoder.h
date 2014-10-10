#pragma once

#include "BlockEncoder.h"

#include<map>

class _4B5BEncoder:public BlockEncoder
{
private:
	std::map<char,char> mapping;
	void output5B(char, std::list<bool>&);
public:
	_4B5BEncoder(void);
	virtual ~_4B5BEncoder(void);

	std::list<bool> encode(const std::forward_list<bool>&);
};