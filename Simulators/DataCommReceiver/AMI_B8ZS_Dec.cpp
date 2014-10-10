#include"AMI_B8ZS_Dec.h"
using namespace std;


AMI_B8ZS_Dec::AMI_B8ZS_Dec(void):LineDecoder(){

}
AMI_B8ZS_Dec::~AMI_B8ZS_Dec(void){}

 std::list<bool> AMI_B8ZS_Dec::decode(const std::list<float>& in){
	 list<bool>result;
	 bool forceZero = false;
	 float lastNonZeroPolatiry = 0;
	 for(float currentSignal : in)
	 {
		  //get characteristic of signal
		float currentPolarity = currentSignal/abs(currentSignal);
		if(abs(currentSignal)<(amplitude/2)) currentPolarity = 0;

		if(currentPolarity == 0)
		{
			result.push_back(false);
		}
		else
		{
			if(currentPolarity == lastNonZeroPolatiry)
			{
				result.push_back(false);
				forceZero = true;
			}
			else
			{
				result.push_back(!forceZero);
				forceZero = false;
			}
			lastNonZeroPolatiry = currentPolarity;

		}

	 }

	 return result;
}