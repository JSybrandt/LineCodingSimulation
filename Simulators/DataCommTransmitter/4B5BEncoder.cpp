#include "4B5BEncoder.h"

using namespace std;

//warning, fugly

_4B5BEncoder::_4B5BEncoder() {
	mapping[0x00]=0x1E;
	mapping[0x01]=0x09;
	mapping[0x02]=0x14;
	mapping[0x03]=0x15;
	mapping[0x04]=0x0A;
	mapping[0x05]=0x0B;
	mapping[0x06]=0x0E;
	mapping[0x07]=0x0F;
	mapping[0x08]=0x12;
	mapping[0x09]=0x13;
	mapping[0x0A]=0x16;
	mapping[0x0B]=0x17;
	mapping[0x0C]=0x1A;
	mapping[0x0D]=0x1B;
	mapping[0x0E]=0x1C;
	mapping[0x0F]=0x1D;
	mapping['K']= 0x11;
	mapping['T']= 0x0D;
}


_4B5BEncoder::~_4B5BEncoder() {
}

list<bool> _4B5BEncoder::encode(const forward_list<bool>& raw_stream) {
	list<bool> output;
	int bitsConsidered = 0;
	char currentSequence = 0x00;
	//start
	output5B(mapping['K'],output);
	for(bool currentBit : raw_stream)
	{
		//make space to left
		currentSequence <<=  1;
		//add in new bit to new space
		currentSequence |= (currentBit?0x01:0x00);
		bitsConsidered++;

		if(bitsConsidered >= 4)
		{
			//output mapped bits
			output5B(mapping[currentSequence],output);
			
			//reset indexes
			currentSequence = 0x00;
			bitsConsidered = 0;
		}

	}
	//stop
	output5B(mapping['T'],output);
	return output;
}

void _4B5BEncoder::output5B(char code, std::list<bool>& result)
{
	//ignore leading 0's
	code <<= 3;
	//add each bit to output
	for(int i = 0 ; i < 5; i++) result.push_back((code<<i)&0x80);
}