/************
 * Example block decoder which simply passes data through.
 *
 * To create your own block decoder, you will need to make another child class of BlockDecoder and override the decode function.
 * Since this is as simple as it gets, there are some things to keep in mind when you implement your own:
 *     - You will likely want a table of blocks for substituting values.
 *	   - You will have to read more than one bit at a time to match against the table of blocks.
 *	   - The length of list that is output should NOT be the length of the input list!
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "BlockPassDec.h"

using namespace std;

BlockPassDec::BlockPassDec() {
}

BlockPassDec::~BlockPassDec() {
}

list<bool> BlockPassDec::decode(const list<bool>& stream) {
	list<bool> output;
	for(auto citer = stream.cbegin(); citer != stream.cend(); ++citer) {
		output.push_back(*citer);
	}

	return output;
}