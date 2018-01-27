#include "gates.h"
#include "net.h"
#include <ostream>

Gate::Gate(string n)
{
	output = NULL;
	inputs = new vector<Net *>;
	inst_name = n;
	delay = 1;
}

Gate::Gate(string n, int d)
{
	output = NULL;
	inputs = new vector<Net *>;
	inst_name = n;
	delay = d;
}

Gate::~Gate()
{
	while(!inputs->empty())
	{
		delete inputs->back();
		inputs->pop_back();
	}
	delete inputs;
	delete output;
}

string Gate::name() const
{
	return inst_name; // conferir o nome
}

int Gate::getDelay() const
{
	return delay;
}

void Gate::addInput(Net *n)
{
	//Net *a = new Net(n->name());
	inputs->push_back(n);///////////////////////////////////////
	inputs->back()->setDelay(n->getDelay());
}

vector<Net *> *Gate::getInputs()
{
	return inputs;
}

void Gate::addOutput(Net *n)
{
	//output = new Net(n->name()); ///////////////////// copy constructor??
	output = n;
	output->setDelay(n->getDelay());
}

Net *Gate::getOutput() const
{
	return output;
}

int Gate::getNumInputs() const
{
	return inputs->size();
}

And::And(string n, int d = 1) : Gate(n, d)
{
}

And::~And()
{
}

char And::eval()
{
	//cout << "??????and";
	int xcount = 0;
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		if((*it)->getVal() == '0') 
		{
			output->setVal('0');
			return '0';
		}
		if((*it)->getVal() == 'X') xcount++;
	}
	if(xcount != 0) return 'X';
	return '1';
}

void And::dump(ostream &os)
{
	//int num = getNumInputs();
	vector<Net *>::iterator it;
	//int num = inputs->size();
	os << "and ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name();
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		// if(it == inputs->begin()) 
		os << ", ";
		os << (*it)->name();
		//if(it != inputs->begin()) os << ", ";
	}
	os << ")";
	//return os;
}

Or::Or(string n, int d = 1) : Gate(n, d)
{
}

Or::~Or()
{
}

char Or::eval()
{
	//cout << "??????OR";
	int xcount = 0;
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		if((*it)->getVal() == '1') return '1';
		if((*it)->getVal() == 'X') xcount++;
	}
	if(xcount != 0) return 'X';
	return '0';
}

void Or::dump(ostream &os)
{
	//int num = inputs->size();
	vector<Net *>::iterator it;
	os << "or ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name();
	for(it = inputs->begin(); it < inputs->end(); ++it)
	{
		// if(it == inputs->begin()) 
		os << ", ";
		os << (*it)->name();
		//if(it != inputs->begin() && it != inputs->end()) os << ", ";
	}
	os << ")";
}

Nor::Nor(string n, int d = 1) : Gate(n, d)
{
}

Nor::~Nor()
{
}

char Nor::eval()
{
	//cout << "??????nOR";
	//int num = inputs->size();
	vector<Net *>::iterator it;
	int xcount = 0;
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		if((*it)->getVal() == '1') return '0';
		if((*it)->getVal() == 'X') xcount++;
	}
	if(xcount != 0) return 'X';
	return '1';
}

void Nor::dump(ostream &os)
{
	//int num = inputs->size();
	vector<Net *>::iterator it;
	os << "nor ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name();
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		// if(it == inputs->begin()) 
		os << ", ";
		os << (*it)->name();
		//if(it != inputs->begin() && it != end()) os << ", ";
	}
	os << ")";
}

Nand::Nand(string n, int d = 1) : Gate(n, d)
{
}

Nand::~Nand()
{
}

char Nand::eval()
{
	//cout << "??????NAND";
	int xcount = 0;
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		if((*it)->getVal() == '0') return '1';
		if((*it)->getVal() == 'X') xcount++;	
	}
	if(xcount != 0) return 'X';
	return '0';
}

void Nand::dump(ostream &os)
{
	//int num = inputs->size();
	vector<Net *>::iterator it;
	os << "nand ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name();
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		/*if(it != inputs->end())*/ 
		os << ", ";
		os << (*it)->name();
		//if(it != inputs->begin() && it != inputs->end()) os << ", ";
	}
	os << ")";
}

Xor::Xor(string n, int d = 1) : Gate(n, d)
{
}

Xor::~Xor()
{
}

char Xor::eval()
{
	int one = 0;
	//cout << "??????XOR";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		if((*it)->getVal() == 'X') return 'X';
		if((*it)->getVal() == '1') one++;
	}
	if(one == 1) return '1';
	return '0';
}

void Xor::dump(ostream &os)
{
	//int num = inputs->size();
	vector<Net *>::iterator it;
	os << "xor ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name();
	for(it = inputs->begin(); it != inputs->end(); ++it)
	{
		// if(it == inputs->begin()) 
		os << ", ";
		os << (*it)->name();
		//if(it != inputs->begin() && it != inputs->end()) os << ", ";
	}
	os << ")";
}

Not::Not(string n, int d = 1) : Gate(n, d)
{
}

Not::~Not()
{
}

char Not::eval()
{
	//for(int i = 0; i < inputs.size(); i++)
	//{
	unsigned int zero = 0;
	unsigned int one = 0;
	// cout << "  NOT";
	vector<Net *>::iterator it = inputs->begin();
	for(unsigned int i = 0; i < inputs->size(); i++)
	{
		// cout << "net name: " << (*it)->name();
		// cout << " (input " << i << "): " << (*it)->getVal() << endl;
		if((*it)->getVal() == 'X')
		{
			// cout << "(*it)->getVal() == 'X'";
			return 'X';	
		} 
		if((*it)->getVal() == '0') zero++;
		else one++;
	}
	if(zero > 0 && one > 0)
	{
		// cout << "------- X -------" << endl;
		return 'X';
	}
	else if(zero > 0)
	{
		// cout << "------- 1 -------" << endl;
		return '1';
	} 
	else 
	{
		// cout << "------- 0 -------" << endl;
		return '0';
	}
}

void Not::dump(ostream &os)
{
	//int num = inputs->size();
	vector<Net *>::iterator it = inputs->begin();
	os << "not ";
	if(getDelay() != 1) os << "#" << getDelay() << " ";
	os << name() << "(" << getOutput()->name() << ", ";
	os << (*it)->name();
	os << ")";
}