///////////////////////////////////////////////////////////////////////////////
////
////  Create dictionaries
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace nuEI+;

#pragma link C++ class nuEI::Database+;
#pragma link C++ class nuEI::Track+;
#pragma link C++ class nuEI::Particle+;
#pragma link C++ class nuEI::SensorHit+;
#pragma link C++ class nuEI::Event+;

#pragma link C++ class std::pair<TLorentzVector,double>+;

#pragma link C++ class std::vector<nuEI::Track*>+;
#pragma link C++ class std::vector<nuEI::Particle*>+;
#pragma link C++ class std::vector<nuEI::SensorHit*>+;
#pragma link C++ class std::vector<std::pair<TLorentzVector,double>>+;
#pragma link C++ class std::vector< std::pair<double, int> >+;

#pragma link C++ class std::map< std::string, int >+;
#pragma link C++ class std::map< int, std::string >+;
#pragma link C++ class std::map< int, double >+;
#pragma link C++ class std::map< int, int    >+;

#endif
