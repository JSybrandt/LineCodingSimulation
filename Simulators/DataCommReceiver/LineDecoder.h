/************
 * Header of the parent class of Line Decoders. Do not edit this file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include <list>

class LineDecoder {
protected:
	float amplitude;
public:
	LineDecoder(void);
	virtual ~LineDecoder(void);

	virtual std::list<bool> decode(const std::list<float>&) = 0;
};

