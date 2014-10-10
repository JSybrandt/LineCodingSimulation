/************
 * Example block encoder which simply passes data through.
 *
 * To create your own block encoder, you will need to make another child class of BlockEncoder and override the encode function.
 * Since this is as simple as it gets, there are some things to keep in mind when you implement your own:
 *     - You will likely want a table of blocks for substituting values.
 *	   - You will have to read more than one bit at a time to match against the table of blocks.
 *	   - The length of list that is output should NOT be the length of the input list!
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "BlockPassEnc.h"

using namespace std;

BlockPassEnc::BlockPassEnc() {
}


BlockPassEnc::~BlockPassEnc() {
}

list<bool> BlockPassEnc::encode(const forward_list<bool>& raw_stream) {
	list<bool> output;
	for(auto citer = raw_stream.cbegin(); citer != raw_stream.cend(); ++citer) {
		output.push_back(*citer);
	}
	return output;
}