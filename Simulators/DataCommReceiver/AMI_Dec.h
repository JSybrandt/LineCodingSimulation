#pragma once

#include "LineDecoder.h"
#include <list>

class AMI_Dec : public LineDecoder {
public:
	AMI_Dec(void);
	~AMI_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};