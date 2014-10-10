/************
 * Example line decoder which implements NRZ-L.
 *
 * Uses a threshold of 2.5V for a "1" otherwise gives a "0." Converts to a list of bool values.
 *
 * Future features: Adjustable voltage threshold
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include "LineDecoder.h"

class NRZ_L_Dec : public LineDecoder {
public:
	NRZ_L_Dec(void);
	~NRZ_L_Dec(void);

	std::list<bool> decode(const std::list<float>&);
};

