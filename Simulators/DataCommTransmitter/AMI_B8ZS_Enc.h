#pragma once

#include "LineEncoder.h"
#include <list>

class AMI_B8ZS_Enc : public LineEncoder {
private:
	std::list<bool> scramblePattern;
public:
	AMI_B8ZS_Enc(void);
	~AMI_B8ZS_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};