/************
 * Class declaration for a pass-through block decoder.
 *
 * For more details see the corresponding .cpp file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include "BlockDecoder.h"

class BlockPassDec : public BlockDecoder {
public:
	BlockPassDec(void);
	~BlockPassDec(void);

	std::list<bool> decode(const std::list<bool>&);
};

