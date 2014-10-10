#pragma once

#include "LineEncoder.h"
#include <list>

class NRZ_I_Enc : public LineEncoder {
public:
	NRZ_I_Enc(void);
	~NRZ_I_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};