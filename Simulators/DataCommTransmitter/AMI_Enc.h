#pragma once

#include "LineEncoder.h"
#include <list>

class AMI_Enc : public LineEncoder {
public:
	AMI_Enc(void);
	~AMI_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};