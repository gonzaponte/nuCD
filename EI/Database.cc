///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "Units.hh"
#include "Database.hh"

ClassImp(nuEI::Database);

namespace nuEI
{
  Database* Database::_instance = 0;

  Database* Database::GetInstance()
  {
    if (!_instance) _instance = new Database();
    return _instance;
  }

  Database::Database()
  { LoadDatabase(); }

  void Database::LoadDatabase()
  {
    const int N = 23;
    int codes[]         = { 22, -11, 11, -13, 13, -15, 15, 12, -12, 14, -14, 16, -16, 211, -211, 111, 321, -321, 2212, -2212, 2112, -2112, 1000020040 };
    std::string names[] = {"gamma","e+","e-","mu+","mu-","tau+","tau-","nu_e","nu_e_bar","nu_mu","nu_mu_bar","nu_tau","nu_tau_bar","pi+","pi-","pi0","K+","K-","p","p_bar","n","n_bar","alpha"};
    double masses[]     = {0.0,0.510998902,0.510998902,105.658357,105.658357,1776.99,1776.99,0.0,0.0,0.0,0.0,0.0,0.0,139.57018,139.57018,134.9766,493.677,493.677,938.27200,938.27200,939.56533,939.56533,3727000.0};
    double charges[]    = {0.0,1.0,-1.0,1.0,-1.0,1.0,-1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,-1.0,0.0,1.0,-1.0,1.0,-1.0,0.0,0.0,2.0};
    double lifetimes[]  = {-1.0,-1.0,-1.0,2.197e-6,2.197e-6,1.291e-15,1.291e-15,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,2.603e-8,2.603e-8,8.4e-17,1.2386e-8,1.2386e-8,-1.0,-1.0,-1.0,-1.0,-1.0};

    for (int i=0; i<N; ++i)
    {
      _codes    [names[i]] = codes    [i];
      _names    [codes[i]] = names    [i];
      _masses   [codes[i]] = masses   [i] * MeV;
      _charges  [codes[i]] = charges  [i];
      _lifetimes[codes[i]] = lifetimes[i] * second;
    }

  }

}  // namespace nuEI
