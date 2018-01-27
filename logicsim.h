#ifndef LOGICSIM_H
#define LOGICSIM_H

#include <ostream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "gates.h"
#include "net.h"
#include "design.h"
#include <iomanip>

using namespace std;

//Forward Declaration
class Design;

class LogicSim
{	
public:
	//Constructor
	LogicSim();

	//Destructor
	~LogicSim();

	//parsing function
	int parse(string file_name, Design *des);

	//function to run simulation 
	//void simulation();

	//dump function
	void dump(ostream &os, Design *des);

private:
	vector<string> input_val;
	vector<Net *> *outputs;
	vector<string> input_name;
	map<string, char> pi_val;
	vector<vector<char> > values;
	vector<vector<int> > delays; 
	// map<string, int> delay;
	// map<string, char> value;
};

#endif