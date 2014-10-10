/************
 * Example line encoder which implements NRZ-L.
 *
 * Uses the value 5.0 for 1 and -5.0 for 0.  Note this transitions from a list of boolean values to a list of floating point values!
 *
 * Future features: Adjustable voltage levels.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "NRZ_L_Enc.h"

using namespace std;

NRZ_L_Enc::NRZ_L_Enc(void):LineEncoder(){
}


NRZ_L_Enc::~NRZ_L_Enc(void) {
}

list<float> NRZ_L_Enc::encode(const list<bool>& in) {
	list<float> output;
	for(auto citer = in.cbegin(); citer != in.cend(); ++citer) {
		if(*citer) {
			output.push_back(-amplitude);
		}
		else {
			output.push_back(amplitude);
		}
	}

	return output;
}