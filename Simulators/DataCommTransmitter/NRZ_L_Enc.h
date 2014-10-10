/************
 * Class declaration for an example line encoder that implements NRZ-L.
 *
 * For more details, see the corresponding .cpp file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include "LineEncoder.h"
#include <list>

class NRZ_L_Enc : public LineEncoder {
public:
	NRZ_L_Enc(void);
	~NRZ_L_Enc(void);

	std::list<float> encode(const std::list<bool>&);
};

