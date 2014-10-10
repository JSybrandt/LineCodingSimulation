/************
 * Implementation of the basic receiver.
 *
 * "Receives" (by reading from a file) and outputs the data as a list of floating point values representing voltages.
 *
 * Future features: adjustable running average window
 *					output of various metrics
 *					exception handling
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#include "Receiver.h"

using namespace std;

//Initializes the baseline to be 0
Receiver::Receiver() {
	runningWindow = new float[16];
	for(int i = 0; i < 16; i++) {
		runningWindow[i] = 0.0f;
	}

	baseline = 0.0f;
}

//Closes the file as cleanup, deletes the buffer of values
Receiver::~Receiver() {
	fin.close();
	delete [] runningWindow;
}

//Tries to open the file provided, returns false if it can't
bool Receiver::setSource(string filename) {
	fin.close();
	fin.open(filename);
	return isValidSource();
}

//Checks to see if the file is open
bool Receiver::isValidSource() {
	return fin.is_open();
}

string Receiver::getSource() {
	return fname;
}

//slides the buffered values down and updates...more efficient calculation possible but this leaves it open for an adjustable window later
void Receiver::updateBaseline(float val) {
	float sum = val;
	for(int i = 15; i > 0; i--) {
		sum += runningWindow[i];
		runningWindow[i] = runningWindow[i-1];
	}
	runningWindow[0] = val;
	
	baseline = sum / 16.0f;
}

//will output an empty list if the file hasn't been set properly, in the future should be an exception
list<float> Receiver::receive() {
	list<float> output;
	
	do {
		float signal;
		fin >> signal;
		if(!fin.fail()) {
			output.push_back(signal - baseline);
			updateBaseline(signal);
		}
	} while(!fin.fail());	//last attempt will cause failure

	return output;
}