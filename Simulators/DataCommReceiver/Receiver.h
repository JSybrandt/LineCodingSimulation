/************
 * Class declaration for the simulated Receiver.
 *
 * For more details see the corresponding .cpp file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include <string>
#include <fstream>
#include <list>

class Receiver {
public:
	Receiver(void);
	~Receiver(void);

	bool setSource(std::string);
	bool isValidSource(void);
	std::string getSource(void);
	
	std::list<float> receive(void);

private:
	void updateBaseline(float);
	float baseline;
	float* runningWindow;

	std::ifstream fin;
	std::string fname;
};

