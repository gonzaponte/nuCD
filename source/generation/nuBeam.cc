// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "generation/nuBeam.hh"

#include "core/DetectorConstruction.hh"
#include "geometry/BaseGeometry.hh"

#include <G4GenericMessenger.hh>
#include <G4ParticleDefinition.hh>
#include <G4RunManager.hh>
#include <G4ParticleTable.hh>
#include <G4PrimaryVertex.hh>
#include <G4Event.hh>
#include <G4RandomDirection.hh>
#include <Randomize.hh>
#include <G4NeutrinoE.hh>
#include <G4OpticalPhoton.hh>

#include "CLHEP/Units/SystemOfUnits.h"

using namespace nuCD;
using namespace CLHEP;


nuBeam::nuBeam():
G4VPrimaryGenerator(), _msg(0), _particle_definition( G4NeutrinoE::Definition() ), _geometry(0),
_Emin(0.), _Emax(0.), _theta(0.), _phi(0.), _x0(0.), _y0(0.), _z0(0.)
{
  _msg = new G4GenericMessenger(this, "/Generator/nuBeam/", "Control commands of nuBeam generator.");
  _msg->DeclareMethod("particle", &nuBeam::SetParticleDefinition, "Set particle to be generated.");

  G4GenericMessenger::Command&
    minE = _msg->DeclareProperty("Emin", _Emin, "Set minimum kinetic energy of the particle.");
    minE.SetUnitCategory("Energy");
    minE.SetParameterName("Emin", false);
    minE.SetRange("Emin>0.");

  G4GenericMessenger::Command&
    maxE = _msg->DeclareProperty("Emax", _Emax, "Set maximum kinetic energy of the particle");
    maxE.SetUnitCategory("Energy");
    minE.SetParameterName("Emax", false);
    minE.SetRange("Emax>0.");

  _msg->DeclareProperty("theta", _theta, "theta angle");
  _msg->DeclareProperty("phi"  , _phi  , "phi angle"  );
  _msg->DeclareProperty("x0"   , _x0   , "x0"         );
  _msg->DeclareProperty("y0"   , _y0   , "y0"         );
  _msg->DeclareProperty("z0"   , _z0   , "z0"         );

  DetectorConstruction* DC =
    (DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  _geometry = DC->GetGeometry();

  _z0 = 0.0;
}

nuBeam::~nuBeam()
{
  delete _msg;
}

void nuBeam::SetParticleDefinition(G4String particle_name)
{
  _particle_definition =  G4ParticleTable::GetParticleTable()->FindParticle(particle_name);

  if (!_particle_definition)
    G4Exception("SetParticleDefinition()", "[nuBeam]", FatalException, "Unknown particle name.");
}

void nuBeam::GeneratePrimaryVertex(G4Event* event)
{
  if (!_z0) _z0 =  _geometry->GetSize();
  G4ThreeVector position = G4ThreeVector( _x0, _y0, _z0 );
  G4double time = 0.;

  G4PrimaryVertex* vertex = new G4PrimaryVertex(position, time);

  // Generate uniform random energy in [E_min, E_max] and compute momentum
  G4double nuE = RandomEnergy();
  G4double px  = nuE * sin(_theta) * cos(_phi);
  G4double py  = nuE * sin(_theta) * sin(_phi);
  G4double pz  = nuE * cos(_theta);

  // Create the new primary particle and set it some properties
  G4PrimaryParticle* particle = new G4PrimaryParticle(_particle_definition, px, py, pz);

  // Add particle to the vertex and this to the event
  vertex->SetPrimary(particle);
  event->AddPrimaryVertex(vertex);
}

G4double nuBeam::RandomEnergy() const
{
  if (_Emax == _Emin) return _Emin;
  else return ( G4UniformRand() * (_Emax - _Emin) + _Emin );
}
