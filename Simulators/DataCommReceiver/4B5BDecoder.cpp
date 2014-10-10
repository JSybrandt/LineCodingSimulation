#include "4B5BDecoder.h"

using namespace std;

//warning, fugly


_4B5BDecoder::_4B5BDecoder() {
	mapping[0x1E]=0x00;
	mapping[0x09]=0x01;
	mapping[0x14]=0x02;
	mapping[0x15]=0x03;
	mapping[0x0A]=0x04;
	mapping[0x0B]=0x05;
	mapping[0x0E]=0x06;
	mapping[0x0F]=0x07;
	mapping[0x12]=0x08;
	mapping[0x13]=0x09;
	mapping[0x16]=0x0A;
	mapping[0x17]=0x0B;
	mapping[0x1A]=0x0C;
	mapping[0x1B]=0x0D;
	mapping[0x1C]=0x0E;
	mapping[0x1D]=0x0F;
	mapping[0x11]='K';
	mapping[0x0D]='T';
}


_4B5BDecoder::~_4B5BDecoder() {
}

std::list<bool> _4B5BDecoder::decode(const std::list<bool>& raw_stream)
{
	list<bool> output;
	int bitsConsidered = 0;
	char currentSequence = 0x00;
	for(bool currentBit : raw_stream)
	{
		//make space to left
		currentSequence <<=  1;
		//add in new bit to new space
		currentSequence |= (currentBit?0x01:0x00);
		bitsConsidered++;

		if(bitsConsidered >= 5)
		{
			//if valid
			if(mapping.count(currentSequence))
			{
				//get equivalent 4b pattern
				currentSequence = mapping[currentSequence];

				//output mapped bits
				if(currentSequence != 'K' && currentSequence!= 'T')output4B(currentSequence,output);
			}
			else
			{
				output.clear();
				cerr<<"4B5B Decoder Found Invalid Bit String."<<hex<<(int)currentSequence<<endl;
				break;
			}
			
			//reset indexes
			currentSequence = 0x00;
			bitsConsidered = 0;
		}

	}
	return output;
}

void _4B5BDecoder::output4B(char code, std::list<bool>& result)
{
	//ignore leading 0's
	code <<= 4;
	//add each bit to output
	for(int i = 0 ; i < 4; i++) result.push_back((code<<i)&0x80);
}