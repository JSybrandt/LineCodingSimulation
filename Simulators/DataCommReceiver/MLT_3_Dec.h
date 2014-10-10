#pragma once

#include "LineDecoder.h"
#include <list>

class MLT_3_Dec : public LineDecoder {
public:
	MLT_3_Dec(void);
	~MLT_3_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};