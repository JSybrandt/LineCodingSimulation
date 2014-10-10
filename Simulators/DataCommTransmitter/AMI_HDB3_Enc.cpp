#include"AMI_HDB3_Enc.h"
using namespace std;


AMI_HDB3_Enc::AMI_HDB3_Enc(void):LineEncoder(){
	scramblePattern.push_back(amplitude);
	scramblePattern.push_back(0);
	scramblePattern.push_back(0);
	scramblePattern.push_back(amplitude);
}
AMI_HDB3_Enc::~AMI_HDB3_Enc(void){}

list<float> AMI_HDB3_Enc::encode(const std::list<bool>& in)
{
	float lastNonZeroPolarity = -1.0;
	bool evenNonZeroElements = false;
	list<float>result;

	int consecutiveZeroCount = 0;

	//loop thru bits
	for(bool currentBit : in)
	{
		//is 1
		if(currentBit)
		{
			//print queued up 0's
			while(consecutiveZeroCount > 0)
			{
				result.push_back(0);
				consecutiveZeroCount--;
			}
			//flip sign
			lastNonZeroPolarity *= -1;
			result.push_back(amplitude*lastNonZeroPolarity);
			evenNonZeroElements = !evenNonZeroElements;
		}
		//is 0
		else
		{
			consecutiveZeroCount++;
		}
		//if we hit 4
		if(consecutiveZeroCount==4)
		{
			//0 if the first scrambled element should be a 0
			float suppressFirstElement = (evenNonZeroElements?1:0);

			//send scrambled pattern
			for(float sigElement : scramblePattern)
			{
				result.push_back(sigElement*lastNonZeroPolarity*suppressFirstElement);
				//make sure to only suppress first bit
				suppressFirstElement = 1;
			}

			//reset count
			consecutiveZeroCount = 0;
			evenNonZeroElements = true;
		}
	}
	//print leftover 0's
	while(consecutiveZeroCount > 0)
	{
		result.push_back(0);
		consecutiveZeroCount--;
	}
	return result;
}