#pragma once

#include "LineDecoder.h"
#include <list>

class NRZ_I_Dec : public LineDecoder {
public:
	NRZ_I_Dec(void);
	~NRZ_I_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};