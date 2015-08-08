///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     08/08/2015
////  @Mofidied 08/08/2015
////
///////////////////////////////////////////////////////////////////////////////


#include "Particle.hh"
#include "Units.hh"
#include "Track.hh"

#include <iostream>
#include <TParticlePDG.h>

ClassImp(nuEI::Particle);

namespace nuEI
{
  Particle::Particle() :
  _particleID(0), _PDGcode(0), _name("Unknown"),
  _mass(0), _charge(0), _lifetime(0), _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0),
  _PDG_manager()
  {  }

  Particle::Particle(int pdg_code) :
  _particleID(0),
  _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0),
  _PDG_manager()
  {
    SetPDGcode(pdg_code);
    _decay_momentum.SetXYZT(0.,0.,0.,_mass);
  }

  Particle::Particle(std::string name) :
  _particleID(0),
  _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0),
  _PDG_manager()
  {
    int code = _PDG_manager.GetParticle(name)->PdgCode();
    *this = Particle(code);
  }

  Particle::~Particle()
  {
    _daughters.Delete();
  }

  void Particle::SetPDGcode( int code )
  {
    _PDGcode = code;
    AddProperties();
  }

  void Particle::AddProperties()
  {
    TParticlePDG* PDGparticle = (TParticlePDG*) _PDG_manager.GetParticle(_PDGcode);
    _name     = PDGparticle->GetName();
    _mass     = PDGparticle->Mass();
    _charge   = PDGparticle->Charge();
    _lifetime = PDGparticle->Lifetime();
  }

  const Particle* Particle::GetMother() const
  {
    if (!_mother.GetObject())
      std::cerr << "======================================= "
                << "Error in nuEI::Particle::GetMother():   "
    		        << "The particle is primary, no mother set. "
                << "======================================= " << std::endl;

    return dynamic_cast<Particle*> (_mother.GetObject());
  }
  //
  // Particle* Particle::GetMother()
  // {
  //   if (!_mother.GetObject()) {
  //     std::cerr << "[ERROR: nuEI::Particle::GetMother()]:"
  //   		<< " the particle is primary, it has no mother!" << std::endl;
  //   }
  //   return dynamic_cast<Particle*> (_mother.GetObject());
  // }

  // Track* Particle::GetTrack(const std::string& det)
  // {
  //   for (int i=0; i< _tracks.GetLast()+1; ++i) {
  //     Track* tr = (Track*)_tracks.At(i);
  //     if (tr->GetDetectorName() == det) {
	//  return tr;
  //     }
  //   }
  //   // std::cerr << "[ERROR: nuEI::Particle::GetTrack()]:"
  //   // 	      << " the particle doesn't have hits from detector "
  //   // 	      << det << std::endl;
  //   return 0;
  //
  // }

  // void Particle::SetName(int code)
  // {
  //   if (code == 22) {
  //     _name = "gamma";
  //     SetParameters(0,0,-1);
  //   } else if (code == -11) {
  //     _name = "e+";
  //     SetParameters(5.10998902E-04*GeV,1,-1);
  //   } else if (code == 11) {
  //     _name = "e-";
  //     SetParameters(5.10998902E-04*GeV,-1,-1);
  //   } else if (code == -13) {
  //     _name = "mu+";
  //     SetParameters(1.05658357E-01*GeV,1,2.197e-6*second);
  //   } else if (code == 13) {
  //     _name = "mu-";
  //     SetParameters(1.05658357E-01*GeV,1,2.197e-6*second);
  //   } else if (code == -15) {
  //     _name = "tau+";
  //     SetParameters(1.77699*GeV,1,291e-15*second);
  //   } else if (code == 15) {
  //     _name = "tau-";
  //     SetParameters(1.77699*GeV,-1,291e-15*second);
  //   } else if (code == 12) {
  //     _name = "nu_e";
  //     SetParameters(0,0,-1);
  //   } else if (code == -12) {
  //     _name = "anti_nu_e";
  //     SetParameters(0,0,-1);
  //   } else if (code == 14) {
  //     _name = "nu_mu";
  //     SetParameters(0,0,-1);
  //   } else if (code == -14) {
  //     _name = "anti_nu_mu";
  //     SetParameters(0,0,-1);
  //   }  else if (code == 16) {
  //     _name = "nu_tau";
  //     SetParameters(0,0,-1);
  //   } else if (code == -16) {
  //     _name = "anti_nu_tau";
  //     SetParameters(0,0,-1);
  //   } else if (code == 211) {
  //     _name = "pi+";
  //     SetParameters(1.3957018E-01*GeV,1,2.603e-8*second);
  //   } else if (code == -211) {
  //     _name = "pi-";
  //     SetParameters(1.3957018E-01*GeV,-1,2.603e-8*second);
  //   } else if (code == 111) {
  //     _name = "pi0";
  //     SetParameters(1.349766E-01*GeV,0,8.4e-17*second);
  //   } else if (code == 321) {
  //     _name = "kaon+";
  //     SetParameters(4.93677E-01*GeV,1,1.2386e-8*second);
  //   } else if (code == -321) {
  //     _name = "kaon-";
  //     SetParameters(4.93677E-01*GeV,-1,1.2386e-8*second);
  //   } else if (code == 130) {
  //     _name = "kaon0L";
  //     SetParameters(4.97672E-01*GeV,0,5.17e-8*second);
  //   } else if (code == 311) {
  //     _name = "kaon0";
  //     SetParameters(4.97672E-01*GeV,0,0.89e-10*second);
  //   } else if (code == 2212) {
  //     _name = "proton";
  //     SetParameters(9.3827200E-01*GeV,1,-1);
  //   } else if (code == -2212) {
  //     _name = "anti_proton";
  //     SetParameters(9.3827200E-01*GeV,-1,-1);
  //   } else if (code == 2112) {
  //     _name = "neutron";
  //     SetParameters(9.3956533E-01*GeV,0,-1);
  //   } else if (code == -2112) {
  //     _name = "anti_neutron";
  //     SetParameters(9.3956533E-01*GeV,0,-1);
  //   } else if (code == 1000020040) {
  //     _name = "alpha";
  //     SetParameters(3.727*GeV,0,-1);
  //   }
  //
  // }


  void Particle::Info(ostream& s) const
  {
    s << std::endl
      << "Particle name:      " << _name       << std::endl
      << "Particle ID:        " << _particleID << std::endl
      << "PDG code:           " << _PDGcode    << std::endl
      << "Mass (MeV):         " << _mass       << std::endl
      << "Charge:             " << _charge     << std::endl;

    s << std::endl
      << "------------------------------------" << std::endl
      << " Production:"                         << std::endl
      << "------------------------------------" << std::endl;

    s << "Volume:               " << _initial_volume << std::endl;
      if (_mother.GetObject())
        s << "Mother:               " << _mother->GetName() << " with ID " << _mother.GetID() << std::endl
          << "Creator process:      " << _creator_process << std::endl;
      else
        s << "Particle is primary   " << std::endl;

    s << "Vertex (mm):          " << _initial_vertex.X()/mm << " " << _initial_vertex.Y()/mm << " " << _initial_vertex.Z()/mm << std::endl
      << "3-momentum (MeV):     " << _initial_momentum.X()/MeV << " " << _initial_momentum.Y()/MeV << " " << _initial_momentum.Z()/MeV << std::endl
      << "Total momentum (MeV): " << InitialMomentum()/MeV << std::endl
      << "Energy (MeV):         " << InitialEnergy()/MeV << std::endl;

    s << std::endl
      << "------------------------------------" << std::endl
      << " Decay:"                         << std::endl
      << "------------------------------------" << std::endl;

    s << "Volume:               " << _decay_volume << std::endl
      << "Vertex (mm):          " << _decay_vertex.X()/mm << " " << _decay_vertex.Y()/mm << " " << _decay_vertex.Z()/mm << std::endl
      << "3-momentum (MeV):     " << _decay_momentum.X()/MeV << " " << _decay_momentum.Y()/MeV << " " << _decay_momentum.Z()/MeV << std::endl
      << "Total momentum (MeV): " << DecayMomentum()/MeV << std::endl
      << "Energy (MeV):         " << DecayEnergy()/MeV << std::endl;

    s << std::endl
      << "------------------------------------" << std::endl
      << " Secondary particles:               " << std::endl
      << "------------------------------------" << std::endl;

    for (int i=0; i<=_daughters.GetLast(); ++i)
    {
      Particle* p = (Particle*) _daughters.At(i);
      s << p->Name() << " with ID "	<< p->GetID << std::endl;
      //   << "Mass (MeV):       " << p->GetMass()/MeV << std::endl
	    //   << "Charge:           " << p->GetCharge()	<< std::endl
      //   << "3-momentum (MeV): " << p->GetInitialMomentum().X()/MeV << " " << p->GetInitialMomentum().Y()/MeV << " " << p->GetInitialMomentum().Z()/MeV << std::endl
      //   << "Total momentum (MeV): " << p->Momentum()/MeV << std::endl;
      // s << "particle energy (MeV)= " << p->Energy()/MeV << std::endl;
    }

    s << std::endl
      << "------------------------------------" << std::endl
      << " True hits:                         " << std::endl
      << "------------------------------------" << std::endl;

    for (int i=0; i<=_tracks.GetLast(); ++i)
    {
      Track* t = (Track*)_tracks.At(i);
      s << *t << std::endl << std::endl;
    }

    s << "Total track length (mm) = " << _track_length()/mm << std::endl;
  }
  //
  // void Particle::SetParticleName(const std::string& name)
  // {
  //   _name = name;
  //
  //   if (name == "gamma"){
  //     SetParameters(0,0,-1);
  //     _PDGcode = 22;
  //   }
  //   else if (name == "e+"){
  //     SetParameters(5.10998902E-04*GeV,1,-1);
  //     _PDGcode  = -11;
  //   }
  //   else if (name == "e-"){
  //     SetParameters(5.10998902E-04*GeV,-1,-1);
  //     _PDGcode  = 11;
  //   }
  //   else if (name == "mu-"){
  //     SetParameters(1.05658357E-01*GeV,-1,2.197e-6*second);
  //     _PDGcode  = 13;
  //   }
  //   else if (name == "mu+"){
  //     SetParameters(1.05658357E-01*GeV,1,2.197e-6*second);
  //     _PDGcode  = -13;
  //   }
  //   else if (name == "tau+"){
  //     SetParameters(1.77699*GeV,1,291e-15*second);
  //     _PDGcode  = -15;
  //   }
  //   else if (name == "tau-"){
  //     SetParameters(1.77699*GeV,-1,2.291e-15*second);
  //     _PDGcode  = 15;
  //   }
  //   else if (name == "nu_e"){
  //     SetParameters(0,0,-1);
  //     _PDGcode  = 12;
  //   }
  //   else if (name == "anti_nu_e"){
  //     SetParameters(0,0,-1);
  //     _PDGcode  = -12;
  //   }
  //   else if (name == "nu_mu"){
  //     SetParameters(0,0,-1);
  //     _PDGcode  = 14;
  //   }
  //   else if (name == "anti_nu_mu"){
  //     SetParameters(0,0,-1);
  //     _PDGcode = -14;
  //   }
  //   else if (name == "nu_tau"){
  //     SetParameters(0,0,-1);
  //     _PDGcode  = 16;
  //   }
  //   else if (name == "anti_nu_tau"){
  //     SetParameters(0,0,-1);
  //     _PDGcode  = -16;
  //   }
  //   else if (name == "pi+"){
  //     SetParameters(1.3957018E-01*GeV,1,2.603e-8*second);
  //     _PDGcode = 211;
  //   }
  //   else if (name == "pi-"){
  //     SetParameters(1.3957018E-01*GeV,-1,2.603e-8*second);
  //     _PDGcode  = -211;
  //   }
  //   else if (name == "pi0"){
  //     SetParameters(1.349766E-01*GeV,0,8.4e-17*second);
  //     _PDGcode  = 111;
  //   }
  //   else if (name == "kaon+"){
  //     SetParameters(4.93677E-01*GeV,1,1.2386e-8*second);
  //     _PDGcode  = 321;
  //   }
  //   else if (name == "kaon-"){
  //     SetParameters(4.93677E-01*GeV,-1,1.2386e-8*second);
  //     _PDGcode  = -321;
  //   }
  //   else if (name == "kaon0L"){
  //     SetParameters(4.97672E-01*GeV,0,5.17e-8*second);
  //     _PDGcode  = 130;
  //   }
  //   else if (name == "kaon0"){
  //     SetParameters(4.97672E-01*GeV,0,0.89e-10*second);
  //     _PDGcode  = 310;
  //   }
  //   else if (name == "proton"){
  //     SetParameters(9.3827200E-01*GeV,1,-1);
  //     _PDGcode  = 2212;
  //   }
  //   else if (name == "anti_proton"){
  //     SetParameters(9.3827200E-01*GeV,-1,-1);
  //     _PDGcode  = -2212;
  //   }
  //   else if (name == "neutron"){
  //     SetParameters(9.3956533E-01*GeV,0,-1);
  //     _PDGcode  = 2112;
  //   }
  //   else if (name == "anti_neutron"){
  //     SetParameters(9.3956533E-01*GeV,0,-1);
  //     _PDGcode = -2112;
  //   }
  //   else if (name == "deuteron"){
  //     SetParameters(1.875613*GeV,0,-1);
  //     _PDGcode  = 0;
  //   }
  //   else if (name == "tritium"){
  //     SetParameters(2.80925*GeV,0,-1);
  //     _PDGcode  = 0;
  //   }
  //   else if (name == "alpha"){
  //     SetParameters(3.727*GeV,0,-1);
  //     _PDGcode  = 0;
  //   }
  //   else if (name == "unknown"){ // assume pion mass
  //     SetParameters(1.3957018E-01*GeV,-1,2.603e-8*second);
  //     _PDGcode  = 0;
  //   }
  //   else if (name == "void"){
  //     SetParameters(0,0,0);
  //     _PDGcode  = 0;
  //   }
  //   else {
  //     SetParameters(0,0,-1);
  //     _PDGcode=0;
  //   }
  //
  // }



} // namespace nuEI

ostream& operator << (ostream& s, const nuEI::Particle& p) {
  p.Info(s);
  return s;
}
