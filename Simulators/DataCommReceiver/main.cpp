/************
 * Base code for receiving in a data communication simulation framework.
 *
 * "Receives" (by reading from a file) and outputs the data as a string.
 *
 * Future features: XML config file format to streamline experiments
 *				    output of various metrics.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 * version 0.1.0
 ************/

#include <iostream>
#include <string>
#include <list>

#include "4B5BDecoder.h"
#include "BlockDecoder.h"
#include "BlockPassDec.h"
#include "Receiver.h"
#include "LineDecoder.h"
#include "NRZ_L_Dec.h"

#include "2B1Q_Dec.h"
#include "AMI_Dec.h"
#include "AMI_B8ZS_Dec.h"
#include "AMI_HDB3_Dec.h"
#include "MLT_3_Dec.h"
#include "NRZ_I_Dec.h"

using namespace std;

int main(int argc, char** argv) {
	while(true){
	BlockDecoder* blockDec;
	LineDecoder* lineDec;
	
	cout << "Welcome to the receiver simulation for Comp 342.\n Remember it's an experimental assignment so let Prof. Boatright know if there are bugs in the framework!" << endl;

	bool responseValid;
	int response;

	/**
	* Get user input to initialize the simulator.
	**/

	//TODO: Add block encoding schemes as necessary by the assignment.
	do {
		cout << "Select the block encoding scheme:" << endl;
		cout << "\t (0) No block encoding" << endl;
		cout << "\t (1) 4B5B encoding" << endl;
		cin >> response;
		responseValid = response == 0||1;
	} while(!responseValid);
	
	switch(response) {
	case 0:
		blockDec = new BlockPassDec;
		break;
	case 1:
		blockDec = new _4B5BDecoder;
		break;
	default:
		cerr << "Invalid response for block encoding." << endl;
		return -1;
	}

		//TODO: Add line Decoding schemes as necessary by the assignment.
	do {
		cout << "Select the line Decoding scheme:" << endl;
		cout << "\t (0) NRZ-L" << endl;
		cout << "\t (1) 2B1Q_Dec.h"<< endl;
		cout << "\t (2) AMI_Dec.h"<< endl;
		cout << "\t (3) AMI_B8ZS_Dec.h"<< endl;
		cout << "\t (4) AMI_HDB3_Dec.h"<< endl;
		cout << "\t (5) MLT_3_Dec.h"<< endl;
		cout << "\t (6) NRZ_I_Dec.h"<< endl;
		cin >> response;
		responseValid = response>=0&&response<=6;
	} while(!responseValid);
	
	switch(response) {
	case 0:
		lineDec = new NRZ_L_Dec();
		break;
	case 1:
		lineDec = new _2B1Q_Dec();
		break;
	case 2:
		lineDec = new AMI_Dec();
		break;
	case 3:
		lineDec = new AMI_B8ZS_Dec();
		break;
	case 4:
		lineDec = new AMI_HDB3_Dec();
		break;
	case 5:
		lineDec = new MLT_3_Dec();
		break;
	case 6:
		lineDec = new NRZ_I_Dec();
		break;
	default:
		cerr << "Invalid response for line Decoding." << endl;
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//																									//
	//						  Begin the "do not edit" part of the framework...							//
	//																									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	Receiver receiver;
	do {
		string filename;
		cout << "Finally, what filename has the message? ";
		cin >> filename;

		filename = "..\\Data\\"+filename;

		if(!receiver.setSource(filename)) {
			cerr << "Could not open the filename provided." << endl;
		}
	} while(!receiver.isValidSource());

	list<float> lineStream = receiver.receive();
	list<bool> blockStream = lineDec->decode(lineStream);
	list<bool> rawStream = blockDec->decode(blockStream);

	int resultsSize = rawStream.size() >> 3;
	char* results = new char[resultsSize+1];	//strings need to be null terminated!
	
	for(int i = 0; i <= resultsSize; i++) {
		results[i] = 0;
	}

	int letter = 0;
	int bit = 7;

	for(auto citer = rawStream.cbegin(); citer != rawStream.cend(); ++citer) {
		results[letter] |= ((*citer) ? 1 : 0) << bit--;	//no contest, this is my favorite line of the entire framework.
		if(bit == -1) {
			letter++;
			bit = 7;
		}
	}

	string finalOutput(results);

	cout << "Received the following message: " << finalOutput << endl;

	system("pause");
	}
	return 0;
}