///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "Database.hh"
#include "Particle.hh"
#include "Units.hh"

ClassImp(nuEI::Particle);

namespace nuEI
{
  Particle::Particle() :
  _particleID(0), _PDGcode(0), _name("Unknown"),
  _mass(0), _charge(0), _lifetime(0), _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0)
  { _PDG_manager = Database::GetInstance(); }

  Particle::Particle(int pdg_code) :
  _particleID(0),
  _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0)
  {
    _PDG_manager = Database::GetInstance();
    SetPDGcode(pdg_code);
    _decay_momentum.SetXYZT(0.,0.,0.,_mass);
  }

  Particle::Particle(std::string name) :
  _particleID(0),
  _track_length(0.), _primary(true),
  _initial_vertex(), _decay_vertex(), _initial_momentum(), _decay_momentum(),
  _initial_volume("Unknown"), _decay_volume("Unknown"), _creator_process("Unknown"),
  _mother(0), _tracks(0), _daughters(0)
  {
    _PDG_manager = Database::GetInstance();
    int code = _PDG_manager->GetPDGcode(name);
    *this = Particle(code);
  }

  Particle::~Particle()
  {
    _daughters.Delete();
  }

  void Particle::AddProperties()
  {
    _name     = _PDG_manager->GetName    (_PDGcode);
    _mass     = _PDG_manager->GetMass    (_PDGcode);
    _charge   = _PDG_manager->GetCharge  (_PDGcode);
    _lifetime = _PDG_manager->GetLifetime(_PDGcode);
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

  void Particle::Info(std::ostream& s) const
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
        s << "Mother:               " << GetMother()->GetParticleName() << " with ID " << GetMother()->GetID() << std::endl
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
      s << p->GetParticleName() << " with ID "	<< p->GetID() << std::endl;
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

    s << "Total track length (mm) = " << _track_length/mm << std::endl;
  }

} // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::Particle& p) {
  p.Info(s);
  return s;
}
