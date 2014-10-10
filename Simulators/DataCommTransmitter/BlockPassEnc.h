/************
 * Class declaration for a pass-through block encoder.
 * 
 * For more details see the corresponding .cpp file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include "BlockEncoder.h"
#include <forward_list>
#include <list>

class BlockPassEnc : public BlockEncoder {
public:
	BlockPassEnc(void);
	~BlockPassEnc(void);

	std::list<bool> encode(const std::forward_list<bool>&);
};

