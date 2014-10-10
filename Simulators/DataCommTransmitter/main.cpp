/************
 * Base code for transmission in a data communication simulation framework.
 *
 * "Transmits" (by saving to a file) the data (a user-provided string).
 *
 * User will also have to provide performance information such as attenuation and SNR.
 *
 * Future features: XML config file format to streamline experiments
 *				    output of various metrics.
 *
 * Created 9/19/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 * version 0.1.1
 ************/

#include <iostream>
#include <string>
#include <forward_list>
#include <list>

#include "4B5BEncoder.h"
#include "BlockEncoder.h"
#include "BlockPassEnc.h"
#include "Transmitter.h"
#include "LineEncoder.h"
#include "NRZ_L_Enc.h"

#include "2B1Q_Enc.h"
#include "AMI_Enc.h"
#include "AMI_B8ZS_Enc.h"
#include "AMI_HDB3_Enc.h"
#include "MLT_3_Enc.h"
#include "NRZ_I_Enc.h"

using namespace std;

int main(int argc, char** argv) {

	while(true)
	{
	BlockEncoder* blockEnc;
	LineEncoder* lineEnc;
	
	cout << "Welcome to the transmitter simulation for Comp 342.\n Remember it's an experimental assignment so let Prof. Boatright know if there are bugs in the framework!" << endl;

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
		blockEnc = new BlockPassEnc;
		break;
	case 1:
		blockEnc = new _4B5BEncoder;
		break;
	default:
		cerr << "Invalid response for block encoding." << endl;
		return -1;
	}

	//TODO: Add line encoding schemes as necessary by the assignment.
	do {
		cout << "Select the line encoding scheme:" << endl;
		cout << "\t (0) NRZ-L" << endl;
		cout << "\t (1) 2B1Q_Enc.h"<< endl;
		cout << "\t (2) AMI_Enc.h"<< endl;
		cout << "\t (3) AMI_B8ZS_Enc.h"<< endl;
		cout << "\t (4) AMI_HDB3_Enc.h"<< endl;
		cout << "\t (5) MLT_3_Enc.h"<< endl;
		cout << "\t (6) NRZ_I_Enc.h"<< endl;
		cin >> response;
		responseValid = response>=0&&response<=6;
	} while(!responseValid);
	
	switch(response) {
	case 0:
		lineEnc = new NRZ_L_Enc();
		break;
	case 1:
		lineEnc = new _2B1Q_Enc();
		break;
	case 2:
		lineEnc = new AMI_Enc();
		break;
	case 3:
		lineEnc = new AMI_B8ZS_Enc();
		break;
	case 4:
		lineEnc = new AMI_HDB3_Enc();
		break;
	case 5:
		lineEnc = new MLT_3_Enc();
		break;
	case 6:
		lineEnc = new NRZ_I_Enc();
		break;
	default:
		cerr << "Invalid response for line encoding." << endl;
		return -1;
	}

	float attenuation;
	float noise;
	cout << "Please give the attenuation of the channel (dB): ";
	cin >> attenuation;
	cout << "Please give the average noise voltage of the channel (V): ";
	cin >> noise;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//																									//
	//						  Begin the "do not edit" part of the framework...							//
	//																									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	Transmitter writer;
	writer.setAttenuation(attenuation);
	writer.setNoise(noise);
	do {
		string filename;
		cout << "Finally, what filename should the simulator use for writing? (will be overwritten if it exists): ";
		cin >> filename;

		filename = "..\\Data\\"+filename;

		if(!writer.setDestination(filename)) {
			cerr << "Could not open the filename provided." << endl;
		}
	} while(!writer.isValidDestination());

	/**
	* Get the message from the user.
	**/
	string message;
	cout << "Now the big part...write a short message to send." << endl;
	cin.ignore();
	getline(cin, message);
	
	forward_list<bool> rawStream;
	auto string_citer = message.cbegin();
	while(string_citer != message.cend()) {
		char currentLetter = *(string_citer++);
		unsigned int mask = 1 << 7;
		for(int i = 0; i < 8; i++, mask = mask >> 1) {
			rawStream.push_front(currentLetter & mask);
		}
	}

	//stream is actually reversed, so flip it
	rawStream.reverse();

	cout <<"Raw:"<<endl;
	for(bool b : rawStream) cout<<(b?1:0);
	cout<<endl;

	//block encoding
	list<bool> blockStream = blockEnc->encode(rawStream);

	cout <<"Post:"<<endl;
	for(bool b : blockStream) cout<<(b?1:0);
	cout<<endl;

	//line encoding
	list<float> lineStream = lineEnc->encode(blockStream);

	//alrighty, now we've got a series of voltages to transmit by sending with "writer"
	for(auto citer = lineStream.cbegin(); citer != lineStream.cend(); ++citer) {
		if(!writer.send(*citer)) {
			cerr << "Somehow the transmission went terribly wrong." << endl;
			return -1;
		}
	}

	cout << "Message successfully sent." << endl;
	system("pause");
	}
	return 0;
}