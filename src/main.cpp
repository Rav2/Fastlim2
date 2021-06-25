#include <iostream>
#include "utilities.hpp"
#include "SLHA.hpp"

int main(int argc, char *argv[])
{
  InputParser inParser(argc, argv);
  bool verbose_param = false;
  if( 1 == argc or inParser.cmdOptionExists("--help") or inParser.cmdOptionExists("-h"))
  {
    inParser.printHelp();
    return 0;
  }
  else if(inParser.cmdOptionExists("--version") or inParser.cmdOptionExists("-v")) inParser.printVersion();
  else if(inParser.cmdOptionExists("--verbose")) verbose_param=true;

  bool const isVerbose = verbose_param;
  
  std::string SLHAfileName(argv[1]);
  LHPC::SlhaParser parser(isVerbose);
  LHPC::MassSpectrumClass::MSSM spectrum( isVerbose, false, true );
  parser.registerSpectrum( spectrum );
  parser.readFile( SLHAfileName );

  LHPC::MassEigenstate& gluinoFermion( spectrum.getGluino() );
  double largestBr( 0.0 );
  std::list< LHPC::MassEigenstate const* > const* decayList( NULL );
  std::list< LHPC::MassEigenstate const* > const* subdecayList( NULL );
  for( size_t whichDecay=0; gluinoFermion.getDecaySet().size() > whichDecay; ++whichDecay )
  {
    if( gluinoFermion.getDecay( whichDecay ).getPairedValue() > largestBr )
    {
      decayList = &(gluinoFermion.getDecay( whichDecay ).getPointerList());
      largestBr = gluinoFermion.getDecay( whichDecay ).getPairedValue();
    }
  }
  std::cout << std::endl
  << "gluino: mass = " << gluinoFermion.getAbsoluteMass()
  << ", decay width = " << gluinoFermion.getDecayWidth()
  << ", largest BR = " << largestBr << std::endl;
  return 0;
}
