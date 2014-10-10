#include "2B1Q_Dec.h"

using namespace std;

_2B1Q_Dec::_2B1Q_Dec(void):LineDecoder() {
}


_2B1Q_Dec::~_2B1Q_Dec(void) {
}

 std::list<bool> _2B1Q_Dec::decode(const std::list<float>& in){
	 list<bool>result;

	 for(float currentSignal : in)
	 {
		 result.push_back(currentSignal>0);
		 result.push_back(abs(currentSignal)<=amplitude*(2/3.0));
	 }
	 
	 return result;
}