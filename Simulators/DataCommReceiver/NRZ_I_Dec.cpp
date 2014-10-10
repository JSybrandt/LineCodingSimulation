#include"NRZ_I_Dec.h"
using namespace std;

NRZ_I_Dec::NRZ_I_Dec(void):LineDecoder(){}
NRZ_I_Dec::~NRZ_I_Dec(void){}

 std::list<bool> NRZ_I_Dec::decode(const std::list<float>& in){
	 float previousPolarity=0;
	 list<bool> result;
	 for(float currentSignal : in)
	 {
		 float currentPolarity = currentSignal/abs(currentSignal);

		 //if we have read in more than one signal
		 if(previousPolarity != 0)
		 {
			 //true if inverted, false if not
			result.push_back(previousPolarity!=currentPolarity);
		 }

		 //record last polarity
		 previousPolarity = currentPolarity;
	 }
	 return result;
}