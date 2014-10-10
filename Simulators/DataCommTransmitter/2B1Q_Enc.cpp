#include "2B1Q_Enc.h"

using namespace std;

_2B1Q_Enc::_2B1Q_Enc(void):LineEncoder() {
}


_2B1Q_Enc::~_2B1Q_Enc(void) {
}

list<float> _2B1Q_Enc::encode(const list<bool>& in) {
	list<float> result;
	float currentLevel = 0;

	for(bool currentBit : in)
	{
		//2nd bit
		if(currentLevel!=0)
		{
			currentLevel *= (currentBit?1/3.0:1);
			result.push_back(currentLevel);
			currentLevel = 0;
		}
		//first bit
		else
		{
			currentLevel = (currentBit?1:-1)*amplitude;
		}
	}
	return result;
}