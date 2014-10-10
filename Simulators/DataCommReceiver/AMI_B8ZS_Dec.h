#pragma once

#include "LineDecoder.h"
#include <list>

class AMI_B8ZS_Dec : public LineDecoder {
private:
	std::list<bool> scramblePattern;
public:
	AMI_B8ZS_Dec(void);
	~AMI_B8ZS_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};