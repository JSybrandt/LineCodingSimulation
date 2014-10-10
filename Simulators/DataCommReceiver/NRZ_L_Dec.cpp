/************
 * Example line decoder which implements NRZ-L.
 *
 * Uses a threshold of 2.5V for a "1" otherwise gives a "0." Converts to a list of bool values.
 *
 * Future features: Adjustable voltage threshold
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "NRZ_L_Dec.h"

using namespace std;

NRZ_L_Dec::NRZ_L_Dec() {
}

NRZ_L_Dec::~NRZ_L_Dec() {
}

list<bool> NRZ_L_Dec::decode(const list<float>& stream) {
	list<bool> output;

	for(auto citer = stream.cbegin(); citer != stream.cend(); ++citer) {
		output.push_back(*citer <= -2.5f);
	}

	return output;
}