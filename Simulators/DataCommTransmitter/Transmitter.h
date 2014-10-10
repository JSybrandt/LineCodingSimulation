/************
 * Class declaration for the transmitter of our simulation framework.
 *
 * For more information, see the corresponding .cpp file.
 *
 * Created 9/21/2014 by Cory D. Boatright for use in COMP 342 at Grove City College
 ************/

#pragma once

#include <random>
#include <string>
#include <fstream>
#include <cmath>

class Transmitter {
public:
	Transmitter(void);
	~Transmitter(void);

	void setAttenuation(float);
	void setNoise(float);
	bool setDestination(std::string);
	float getAttenuation(void);
	float getNoise(void);
	std::string getDestination(void);

	bool send(float);
	bool isValidDestination(void);

private:
	float degrade(float);

	float attenuation;
	float noise;

	std::ofstream fout;
	std::string fname;
	std::mt19937 rng;
	std::normal_distribution<float> sampler;
	std::bernoulli_distribution posneg;
};

