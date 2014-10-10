#pragma once

#include "LineEncoder.h"
#include <list>

class MLT_3_Enc : public LineEncoder {
public:
	MLT_3_Enc(void);
	~MLT_3_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};