#include"MLT_3_Enc.h"
using namespace std;

MLT_3_Enc::MLT_3_Enc(void):LineEncoder(){
}
MLT_3_Enc::~MLT_3_Enc(void){}

list<float> MLT_3_Enc::encode(const std::list<bool>& in)
{
	float lastNonZeroPolatiry = -1;
	float lastElementSent = 0;
	bool sendZero = true;
	list<float>result;

	for(bool currentBit : in)
	{
		//if 1
		if(currentBit)
		{
			//if we were at 0 node
			if(lastElementSent==0)
			{
				//flip polatiry
				lastNonZeroPolatiry*=-1;

				//send nonzero
				lastElementSent = amplitude*lastNonZeroPolatiry;
			}
			//we were nonzero
			else
			{
				//return to zero
				lastElementSent = 0;
			}
		}
		//no word done if 0;
		//send data
		result.push_back(lastElementSent);
	}


	return result;
}