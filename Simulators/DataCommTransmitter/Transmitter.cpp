/************
 * Implementation of the basic transmitter.
 *
 * "Transmits" (by writing to a file) and also includes attenuation and the insertion of noise into the signal.
 *
 * Future features: Better handling of noise.
 *					Exception handling.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "Transmitter.h"

#include <chrono>

using namespace std;

//creates a pseudorandom number generator and seeds it with the current system time.
Transmitter::Transmitter() {
	attenuation = 0;
	noise = 0;

	unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
	rng = mt19937(seed);
	posneg = bernoulli_distribution(0.5f);
}

//automatically closes the output file
Transmitter::~Transmitter() {
	fout.close();
}

void Transmitter::setAttenuation(float val) {
	attenuation = val;
}

void Transmitter::setNoise(float val) {
	noise = val;
	sampler = normal_distribution<float>(noise, noise + 0.01f);	//there's probably a more accurate way to generate noise...but this will do for now
}

//opens the output file using the name provided; returns false if there is an error (most likely null string filename)
bool Transmitter::setDestination(string filename) {
	fout.close();
	fout.open(filename);
	return isValidDestination();
}

string Transmitter::getDestination() {
	return fname;
}

bool Transmitter::isValidDestination() {
	return fout.is_open();
}

float Transmitter::getAttenuation() {
	return attenuation;
}

float Transmitter::getNoise() {
	return noise;
}

//takes a signal value and writes the degraded signal to the text file.
bool Transmitter::send(float val) {
	if(!fout.is_open()) {
		return false;
	}

	fout << degrade(val) << " ";

	return true;
}

//attenuates the signal and adds noise
float Transmitter::degrade(float in) {
	//TODO: add signal attenuation!
	//solve the equation for decibels using voltages for V_2 (look in your textbook, page 77) and modify "in" accordingly!
	in *= pow(10,attenuation/20);

	//generate some noise
	float noiseChange = (posneg(rng)) ? sampler(rng) : -sampler(rng);
	in += noiseChange;
	return in;
}