#include"NRZ_I_Enc.h"
using namespace std;

NRZ_I_Enc::NRZ_I_Enc(void):LineEncoder(){}
NRZ_I_Enc::~NRZ_I_Enc(void){}

list<float> NRZ_I_Enc::encode(const std::list<bool>& in)
{
	float lastVoltage = 5.0f;
	list<float>result;

	//inital positive reading
	result.push_back(lastVoltage);

	//loop thru bits
	for(bool currentBit : in)
	{
		//is 1, invert
		if(currentBit)
		{
			lastVoltage*=-1;
		}
		result.push_back(lastVoltage);
	}

	return result;
}