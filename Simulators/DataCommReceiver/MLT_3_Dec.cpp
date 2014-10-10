#include"MLT_3_Dec.h"
using namespace std;

MLT_3_Dec::MLT_3_Dec(void):LineDecoder(){
}
MLT_3_Dec::~MLT_3_Dec(void){}

 std::list<bool> MLT_3_Dec::decode(const std::list<float>& in){
	 list<bool>result;
	 float previousPolarity=0;
	 for(float currentSignal : in)
	 {
		 float currentPolarity = currentSignal/abs(currentSignal);
		 if(abs(currentSignal)<(amplitude/2)) currentPolarity = 0;

		//true if inverted, false if not
		result.push_back(previousPolarity!=currentPolarity);

		 //record last polarity
		 previousPolarity = currentPolarity;
	 }
	 return result;
}