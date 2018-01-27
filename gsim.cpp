// Fabio Ugalde Pereira and Eduardo Ferreira
// ID: 6920789037           ID: 7421857620
// EE355 - Spring 2016
// University of Southern California
//--------------------------------------------------
#include <iostream>
#include <fstream>

#include "vlg_parser.h"
#ifdef AUTOPARSE
#include "vlg_parser_auto.h"
#else
#include "vlg_parser_man.h"
#endif

#include "design.h"
#include "gates.h"
#include "net.h"
#include "logicsim.h"


using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 3){
    cerr << "Usage ./gsim infile.v infile.sim outfile.out" << endl;
    return 1;
  }
#ifdef AUTOPARSE
  VlgParser *parser = new VlgParserAuto();
#else
  VlgParser *parser = new VlgParserMan();
#endif
  Design *d = parser->parse(argv[1]);
  LogicSim lg;

  // Add more of your code here to simply dump the design back
  // out to a file named output.v
  ostream &os();
  ofstream ofile(argv[3]);
  if(lg.parse(argv[2], d) == 0)
  {
    lg.dump(ofile, d);
  }
  ofile.close();
  //Logicsim *ls = new Logicsim();

  //delete ls;
  delete parser;

  return 0;
}

