#include"AMI_Dec.h"
using namespace std;


AMI_Dec::AMI_Dec(void):LineDecoder(){}
AMI_Dec::~AMI_Dec(void){}


 std::list<bool> AMI_Dec::decode(const std::list<float>& in){
	 list<bool>result;
	 float previousPolarity=0;

	 for(float currentSignal : in)
	 {
		 float currentPolarity = currentSignal/abs(currentSignal);
		 
		 if(abs(currentSignal)<(amplitude/3)) currentPolarity = 0;

		//1 if non zero
		result.push_back(currentPolarity!=0);

	 }
	 return result;
}