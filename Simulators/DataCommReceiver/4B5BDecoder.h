#pragma once

#include "BlockDecoder.h"
#include<map>
#include<iostream>

class  _4B5BDecoder : public BlockDecoder {
private:
	std::map<char,char> mapping;
	void output4B(char, std::list<bool>&);
public:
	_4B5BDecoder(void);
	~_4B5BDecoder(void);

	std::list<bool> decode(const std::list<bool>&);
};