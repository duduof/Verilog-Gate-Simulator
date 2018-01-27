#include "logicsim.h"
#include "design.h"

LogicSim::LogicSim()
{}

LogicSim::~LogicSim()
{
	delete outputs;
}


int LogicSim::parse(string file_name, Design* des)
{
	ifstream sim_file(file_name.c_str());
	string myline;
	outputs = des->getPONets();
	/////////////////////////////////////////////////
	//Check if file can be read
	if( !sim_file.good() ) 
	{
		cout  << "Could not read file!" << endl;
		return 1;
	}
	//////////////////////////////////////////////////
	//gets line
	getline( sim_file, myline);

	//////////////////////////////////////////////////
	//1st Error Check -  Do the inputs exist within PIs?
	stringstream in(myline.c_str());
	string in_word;

	vector<Net *> *PI_inputs = des->getPINets();
	vector<Net *>::iterator it;

	unsigned int cnt = 0;
	bool comp = false;
	while( in >> in_word )
	{
		for( it = PI_inputs->begin();
		 it != PI_inputs->end();
		 ++it)
		{
			if( in_word == (*it)->name() )
			{
				comp = true;
				break;
			}
		}
		if(!comp)
		{
			cout << "Sim. file input not a member of input list!" << endl;
			return 1;
		}
		comp = false;
		input_name.push_back(in_word);
		cnt++;
	}

	//////////////////////////////////////////////////
	//2nd Error Check -  Does the number of inputs match?
	if( cnt != PI_inputs->size() )
	{
		cout << "Wrong number of input entries" << endl;
		return 1;
	}

	//////////////////////////////////////////////////
	//3rd Error Check -  Do the inputs have good values?
	while( getline( sim_file, myline) )
	{
		stringstream ss3(myline);
		string error_3;
		while( ss3 >> error_3 )
		{
			if( (*(error_3.c_str()) != 48) // '0'
				&& (*(error_3.c_str()) != 49) //'1')
					&& (*(error_3.c_str()) != 88))//'X') )
			{
				cout << "Wrong values used as inputs. ";
				cout << "Please use '0' or '1' or 'X' " << endl;
				return 1;
			}	
		}
		input_val.push_back(myline);
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	// Toposort
	vector<Net *> *sorted = des->toposort();

	vector<string>::iterator it_v;

	for(it_v = input_val.begin(); it_v != input_val.end(); ++it_v)
	{
		stringstream element(*it_v);
		string aux;
		vector<string>::iterator it_names;
		
		it_names = input_name.begin();
		while(element >> aux) // take every word from the line
		{
			// Net *n = des->findNet(*it_names);
			// n->setVal(*(aux.c_str())); // set nets to element value
			des->findNet(*it_names)->setVal(*(aux.c_str()));
			// cout << "set val: " << des->findNet(*it_names)->getVal() << endl;
			it_names++;
			if(it_names == input_name.end()) break;
		}
		for(it = sorted->begin(); it != sorted->end(); ++it)
		{
			des->findNet((*it)->name())->setVal((*it)->computeVal());
			des->findNet((*it)->name())->setDelay((*it)->computeDelay());
			// value[(*it)->name()] = (*it)->computeVal();
			// value[(*it)->name()] = des->findNet((*it)->name())->getVal();
			// delay[(*it)->name()] = (*it)->computeDelay();
			// cout << "------------------------------" << endl;
			// cout << "name: " << (*it)->name() << "\t";
			// cout << "value: " << des->findNet((*it)->name())->getVal() << endl;
			// cout << "------------------------------" << endl;
		}
		vector<char> actualValues;
		vector<int> actualDelays;
		//cout << "value and delay #" << endl;
		for(unsigned int i = 0; i < outputs->size(); i++)
		{
			actualValues.push_back((*outputs)[i]->getVal());
			actualDelays.push_back((*outputs)[i]->getDelay());

			// cout << actualValues.back() << " ";
			// cout << actualDelays.back() << endl;
		}
		values.push_back(actualValues);
		delays.push_back(actualDelays);
	}

	delete PI_inputs;
 	delete sorted;
 	return 0;
}
void LogicSim::dump(ostream &os, Design* des)
{
	vector<string>::iterator it;
	for(it = input_name.begin(); it != input_name.end(); ++it)
	{
		os << *it << setw(3);
	}
	os << " => ";

	// map<string, char>::iterator it_m1;
	// map<string, int>::iterator it_m2;
	vector<Net *> *pos = des->getPONets();
	vector<Net *>::iterator it_net;
	for(it_net = pos->begin(); it_net != pos->end(); ++it_net)
	{
		os << (*it_net)->name() << setw(3);
		//cout << (*it_net)->name() << setw(3) << (*it_net)->getVal() << endl;
	}

 	// 
 	//for(it = input_val.begin(); it != input_val.end(); ++it)
 	// cout << "val size: " << input_val.size() << endl;
 	for(unsigned int i = 0; i < input_val.size(); i++)
 	{
 		os << endl;
 		// os << *it << " => "; 
 		os << input_val[i] << " => ";
 		// vector<char> currValues;
 		// for(unsigned int j = 0; j < values[i].size(); j++)
 		// {
 		// 	currValues.push_back(values[i][j]);
 		// }
 		vector<char> currValues = values[i];
		vector<int> currDelays = delays[i];
		// cout << "curr size: " << currValues.size();
 		//for(it_net = pos->begin(); it_net != pos->end(); ++it_net)
		for(unsigned int j = 0; j < currValues.size(); j++)
		{
			os << currValues[j] << "@" << currDelays[j];
 			// os << (value.find((*it_net)->name()))->second;
 			// os << "@" << (delay.find((*it_net)->name()))->second;
 			os << setw(2);
 		}
 	}

 	delete pos;
}