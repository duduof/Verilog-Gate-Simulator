#include "net.h"
#include "gates.h"

Net::Net(string n) 
{
	netname = n; 
	delay = 0;
	val = 'X'; 
	drivers = new vector<Gate *>;
	loads = new vector<Gate *>;
}

Net::~Net()
{
	delete drivers;
	delete loads;
}

string Net::name() const
{
	return netname;
}

void Net::addDriver(Gate *g)
{
	drivers->push_back(g);
}

void Net::addLoad(Gate *g)
{
	loads->push_back(g);
}

vector<Gate *> *Net::getLoads()
{
	return loads;
}

vector<Gate *> *Net::getDrivers()
{
	return drivers;
}

char Net::computeVal()
{
	// vector<Gate *> *drivers;
	vector<char> val;
	vector<Gate *>::iterator it;
	// cout << "this net val: " << getVal() << " name " << name() << endl;
	char val_ = getVal();
	for(it = drivers->begin(); it != drivers->end(); ++it)
	{
		val.push_back((*it)->eval());
		setVal(val.back());
		// cout << name() << "\t" << val.back() << " " << endl;
	}
	
	for(unsigned int i = 1; i < val.size(); ++i)
	{
		//cout << "vals " << val[i - 1] << " " << val[i];
		if(val[i - 1] != val[i]) 
		{
			// cout << "outputs nao concordam " << endl;
			setVal('X');
			return 'X';
		}
	}
	val_ = getVal();
	// cout << "saindo da computeVal: " << val_ << endl;
	if(drivers->size() == 0)
		return getVal();
	//setVal(val_);
	return val_;
}

int Net::computeDelay()
{
	int max_net = 0;
	int max = 0;
	vector<Gate *>::iterator it;
	vector<Net *>::iterator it2;
	for(it = drivers->begin(); it != drivers->end(); ++it)
	{
		//d += (*it)->getDelay();
		vector<Net *> *temp_input = (*it)->getInputs();
		for(it2 = temp_input->begin(); it2 != temp_input->end(); ++it2)
		{ 
			if((*it2)->getDelay() > max_net)
			{
				max_net = (*it2)->getDelay();
			}
		}
		if((*it)->getDelay() + max_net > max)
		{
			max = (*it)->getDelay() + max_net;
		}
	}

	setDelay(max);
	return max; 
}

void Net::printDriversLoads()
{
	vector<Gate *>::iterator it;
	for(it = drivers->begin(); it != drivers->end(); ++it)
	{
		cout << (*it)->name();
	}
}