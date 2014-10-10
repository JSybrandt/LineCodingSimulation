#include"AMI_B8ZS_Enc.h"
using namespace std;


AMI_B8ZS_Enc::AMI_B8ZS_Enc(void):LineEncoder(){
	scramblePattern.push_back(0);
	scramblePattern.push_back(0);
	scramblePattern.push_back(0);
	scramblePattern.push_back(amplitude);
	scramblePattern.push_back(-amplitude);
	scramblePattern.push_back(0);
	scramblePattern.push_back(-amplitude);
	scramblePattern.push_back(amplitude);
}
AMI_B8ZS_Enc::~AMI_B8ZS_Enc(void){}

list<float> AMI_B8ZS_Enc::encode(const std::list<bool>& in)
{
	float lastNonZeroPolarity = -1.0;
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
		}
		//is 0
		else
		{
			consecutiveZeroCount++;
		}
		//if we hit 8
		if(consecutiveZeroCount==8)
		{
			//send scrambled pattern
			for(float sigElement : scramblePattern)
			{
				result.push_back(sigElement*lastNonZeroPolarity);
			}
			//reset count
			consecutiveZeroCount = 0;
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