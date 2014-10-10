#include"AMI_Enc.h"
using namespace std;


AMI_Enc::AMI_Enc(void):LineEncoder(){}
AMI_Enc::~AMI_Enc(void){}

list<float> AMI_Enc::encode(const std::list<bool>& in)
{
	float lastNonZeroPolarity = 1.0f;
	list<float>result;

	//loop thru bits
	for(bool currentBit : in)
	{
		//is 1, invert
		if(currentBit)
		{
			result.push_back(amplitude*lastNonZeroPolarity);
			lastNonZeroPolarity*=-1;
		}
		else result.push_back(0);
		
	}

	return result;
}