#pragma once

#include "LineDecoder.h"
#include<queue>
#include <list>

class AMI_HDB3_Dec : public LineDecoder {
private:
	std::list<bool> scramblePattern;
public:
	AMI_HDB3_Dec(void);
	~AMI_HDB3_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};