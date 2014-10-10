#pragma once

#include "LineEncoder.h"
#include <list>

class AMI_HDB3_Enc : public LineEncoder {
private:
	std::list<bool> scramblePattern;
public:
	AMI_HDB3_Enc(void);
	~AMI_HDB3_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};