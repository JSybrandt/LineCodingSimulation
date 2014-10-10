#pragma once

#include "LineEncoder.h"
#include <list>

class _2B1Q_Enc : public LineEncoder {
public:
	_2B1Q_Enc(void);
	~_2B1Q_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};