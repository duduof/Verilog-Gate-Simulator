//Fabio Ugalde Pereira and Eduardo de Oliveira Ferreira
//EE355

#include "design.h"
#include "net.h"
#include <queue>

Design::Design(string n)
{
	desname = n;
}

Design::~Design()
{
	delete sorted;
}

string Design::name()
{
	return desname;
}

void Design::addPI(string n)
{
	pis.push_back(n);
}

void Design::addPO(string n)
{
	pos.push_back(n);
}

Net *Design::findNet(string net_name)
{
	map<string, Net*>::iterator it = designNets.find(net_name);
	
	if( it != designNets.end() )
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

Gate *Design::findGate(string inst_name)
{
	map<string, Gate*>::iterator it = designGates.find(inst_name);
	
	if( it != designGates.end() )
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

Net* Design::addFindNet(string n)
{
	map<string, Net*>::iterator it = designNets.find(n);
	
	if( it != designNets.end() )
	{
		return it->second;
	}
	else
	{
		Net* new_net = new Net(n);
		designNets[n] = new_net;   //add to map
		return new_net;
	}
}

Gate* Design::addFindGate(int gtype, string g)
{
	map<string, Gate*>::iterator it = designGates.find(g);

	if( it != designGates.end() )
	{
		return it->second;
	}
	else
	{
		if( gtype == 0 )				//AND
		{
			Gate* new_and = new And(g, 1);
			designGates[g] = new_and;
			return new_and;
		}	
		else if( gtype == 1 )			//OR
		{
			Gate* new_or = new Or(g, 1);
			designGates[g] = new_or;
			return new_or;
		}
		else if( gtype == 2 )			//NAND
		{
			Gate* new_nand = new Nand(g, 1);
			designGates[g] = new_nand;
			return new_nand;
		}
		else if( gtype == 3 )			//NOR
		{
			Gate* new_nor = new Nor(g, 1);
			designGates[g] = new_nor;
			return new_nor;
		}
		else if( gtype == 4 )			//XOR
		{
			Gate* new_xor = new Xor(g, 1);
			designGates[g] = new_xor;
			return new_xor;
		}
		else if( gtype == 5 )			//NOT
		{
			Gate* new_not = new Not(g, 1);
			designGates[g] = new_not;
			return new_not;
		}
		else
		{
			return it->second;
		}
	}
}

Gate* Design::addFindGate(int gtype, string g, int d)
{
	map<string, Gate*>::iterator it = designGates.find(g);

	if( it != designGates.end() )
	{
		return it->second;
	}
	else
	{
		if( gtype == 0 )				//AND
		{
			Gate* new_and = new And(g, d);
			designGates[g] = new_and;
			return new_and;
		}	
		else if( gtype == 1 )			//OR
		{
			Gate* new_or = new Or(g, d);
			designGates[g] = new_or;
			return new_or;
		}
		else if( gtype == 2 )			//NAND
		{
			Gate* new_nand = new Nand(g, d);
			designGates[g] = new_nand;
			return new_nand;
		}
		else if( gtype == 3 )			//NOR
		{
			Gate* new_nor = new Nor(g, d);
			designGates[g] = new_nor;
			return new_nor;
		}
		else if( gtype == 4 )			//XOR
		{
			Gate* new_xor = new Xor(g, d);
			designGates[g] = new_xor;
			return new_xor;
		}
		else if( gtype == 5 )			//NOT
		{
			Gate* new_not = new Not(g, d);
			designGates[g] = new_not;
			return new_not;
		}
		else
		{
			return it->second;
		}
	}
}

vector<Net *> *Design::getPINets()
{
	map<string, Net *>::iterator it_map;
	vector<string>::iterator it_vec;
	vector<Net *> *PInets = new vector<Net *>;

	for( it_map = designNets.begin(); it_map != designNets.end(); 
		++it_map)
	{
		for( it_vec = pis.begin(); it_vec != pis.end(); ++it_vec)
		{
			if( it_map->first == *it_vec )
			{
				//Net* new_net = new Net(it_map->first);
				PInets->push_back(it_map->second);
			}
		}
	}

	return PInets;
}

vector<Net *> *Design::getPONets()
{
	map<string, Net *>::iterator it_map;
	vector<string>::iterator it_vec;
	vector<Net *> *POnets = new vector<Net *>;

	for( it_map = designNets.begin(); it_map != designNets.end(); 
		++it_map)
	{
		for( it_vec = pos.begin(); it_vec != pos.end(); ++it_vec)
		{
			if( it_map->first == *it_vec )
			{
				//Net* new_net = new Net(it_map->first);
				POnets->push_back(it_map->second);
			}
		}
	}

	return POnets;
}

vector<Net *> *Design::getWireNets()
{
	
	map<string, Net *>::iterator it_map;
	vector<string>::iterator it_pis;
	vector<string>::iterator it_pos;
	vector<Net *> *Wires = new vector<Net *>;
	int test = 0;

	for( it_map = designNets.begin(); it_map != designNets.end(); 
		++it_map)
	{
		for(it_pis = pis.begin(); it_pis != pis.end(); ++it_pis)
		{
			if( it_map->first == *it_pis )
				test++;
		}
		for(it_pos = pos.begin(); it_pos != pos.end(); ++it_pos)
		{
			if( it_map->first == *it_pos )
				test++;
		}

		if( test == 0 )
		{
			//Net* new_net = new Net(it_map->first);
			Wires->push_back(it_map->second);
		}

		test = 0;
	}

	return Wires;
}

vector<Net *> *Design::allNets()
{
	vector<Net *> *allnets = new vector<Net *>;
	map<string, Net *>::iterator it;

	for( it = designNets.begin(); it != designNets.end(); ++it )
	{
		allnets->push_back(it->second);
	}

	return allnets;
}

vector<Gate *> *Design::allGates()
{
	vector<Gate *> *allgates = new vector<Gate *>;
	map<string, Gate *>::iterator it;

	for( it = designGates.begin(); it != designGates.end(); ++it)
	{
		allgates->push_back(it->second);
	}

	return allgates;
}

bool find0(map<string, int> m)
{
	map<string, int>::iterator it;
	for(it = m.begin(); it != m.end(); ++it)
	{
		if(it->second == 0) return true;
	}
	return false;
}

void Design::dfs_visit(string node, vector<Net *> *sorted)
{
	visited[node] = GRAY;
	Net* temp_net = designNets[node];
	vector<Gate *>::iterator it;
	for(it = (temp_net->getDrivers())->begin();
		it != (temp_net->getDrivers())->end();
		++it)
	{
		vector<Net *>::iterator it2;
		for(it2 = ((*it)->getInputs())->begin(); it2 != ((*it)->getInputs())->end(); ++it2)
		{
			if(visited[(*it2)->name()] == WHITE) 
				dfs_visit((*it2)->name(), sorted);
		}
	}
	visited[node] = BLACK;
	sorted->push_back(designNets[node]);
}

vector<Net *> *Design::toposort()
{
	// vector<Net *> *sorted = new vector<Net *>;
	
	sorted = new vector<Net *>;

	//initializes map for visited status
	map<string, Net *>::iterator it;
	for(it = designNets.begin(); it != designNets.end(); ++it)
	{
		visited[it->first] = WHITE;
	}
	// for each vertex
	for(it = designNets.begin(); it != designNets.end(); ++it)
	{
		if(visited[it->first] == WHITE) 
			dfs_visit(it->first, sorted);
	}

	return sorted;
}

void Design::dump(ostream &os)
{
	os << "module ";
	os << desname << "(";
	///////////////////////////////////////////////////////
	vector<string>::iterator it_pis = pis.begin();
	vector<string>::iterator it_pos = pos.begin();

	os << *it_pis;
	for(it_pis += 1; it_pis != pis.end(); ++it_pis)
	{
		os << ", ";
		os << *it_pis;
	}
	os << ", ";
	os << *it_pos;
	for(it_pos += 1; it_pos != pos.end(); ++it_pos)
	{
		os << ", ";
		os << *it_pos;
	}
	os << ");" << endl;
	///////////////////////////////////////////////////////
	//inputs
	for(it_pis = pis.begin(); it_pis != pis.end(); ++it_pis)
	{
		os << "\t" << "input " << *it_pis << ";" << endl;
	}
	///////////////////////////////////////////////////////
	//outputs
	for(it_pos = pos.begin(); it_pos != pos.end(); ++it_pos)
	{
		os << "\t" << "output " << *it_pos << ";" << endl;
	}
	///////////////////////////////////////////////////////	
	//wires
	vector<Net *> *wires;
	wires = getWireNets();

	vector<Net *>::iterator it;

	for(it = wires->begin(); it != wires->end(); ++it)
	{
		os << "\t" << "wire   " << (*it)->name() << ";" << endl;
	}
	os << endl;
	///////////////////////////////////////////////////////
	map<string, Gate *>::iterator it_gate;

	for(it_gate = designGates.begin();
		it_gate != designGates.end();
		++it_gate)
	{
		os << "\t";
		(it_gate->second)->dump(os);
		os << ";" << endl;
	}
	///////////////////////////////////////////////////////
	os << "endmodule" << endl;
	///////////////////////////////////////////////////////
	//deletes
	vector<Net *>::iterator it_2;
	for(it_2 = wires->begin(); it_2 != wires->end(); ++it_2)
	{
		delete *it_2;
	}

	delete wires;
}


bool Design::isPI(Net *n)
{
	vector<string>::iterator it;

	for(it = pis.begin(); it != pis.end(); ++it)
	{
		if( *it == n->name() ) return 1;
	}

	return 0;
}

bool Design::isPO(Net *n)
{
	vector<string>::iterator it;

	for(it = pos.begin(); it != pos.end(); ++it)
	{
		if( *it == n->name() ) return 1;
	}

	return 0;
}

// void Design::dfs_visit(Net *n, vector<Net *> *flist, map<string, int> &colormap)
// {
// 	return;
// }

	/////////////////////////////////////////////////////////////
	//adds pos to queue
	/*queue<string> pos_q;
	vector<string>::iterator it_1;

	for(it_1 = pos.begin(); it_1 != pos.end(); ++it_1)
	{
		pos_q.push(*it_1);
		visited[*it_1] = 1;
	}*/




	/*
	for(unsigned int i = 0; i < pos.size(); i++)
	{
		Net* temp_out = designNets[pos[i]];
		////////////////
		vector<Gate *>::iterator it = (temp_out->getDrivers)->begin();
	}
	*/

	/////////////////////////////////////////////////////////////
	// map<string, int>::iterator it;
	// while( find0(visited) )
	// {	
	// 	map<string, int>::iterator it;
	// 	for(it = designGates.begin(); it != designGates.end(); ++it)
	// 	{
	// 		if(visited[it->first] == 0) topohelper(it->first);
	// 	}
	// 	// string temp = pos_q.pop();      //retrieves output

	// 	// Net* temp_net = designNets[temp];  //Net from given output

	// 	// vector<Gate *> all_drivers = temp_net->getDrivers(); //Drivers from Net

	// }