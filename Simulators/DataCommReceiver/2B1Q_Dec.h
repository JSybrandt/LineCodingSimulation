#pragma once

#include "LineDecoder.h"
#include <list>

class _2B1Q_Dec : public LineDecoder {
public:
	_2B1Q_Dec(void);
	~_2B1Q_Dec(void);

	 std::list<bool> decode(const std::list<float>&);
};