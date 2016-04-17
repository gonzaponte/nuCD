// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 23rd 2015
//
// ----------------------------------------------------------------------------

#include "core/manager/GeneratorManager.hh"

#include <G4GenericMessenger.hh>
#include <G4VPrimaryGenerator.hh>

using namespace nuCD;


GeneratorManager::GeneratorManager(): _msg(0)
{
  _msg = new G4GenericMessenger(this, "/Generator/");
  _msg->DeclareProperty("RegisterGenerator", _name, "");
}


GeneratorManager::~GeneratorManager()
{
  delete _msg;
}


//////////////////////////////////////////////////////////////////////

#include "generation/nuBeam.hh"

G4VPrimaryGenerator* GeneratorManager::CreateGenerator() const
{
  G4VPrimaryGenerator* p = 0;

  if (_name == "NU_BEAM") p = new nuBeam();

  else
  {
    G4String err = "The user specified an unknown generator: " + _name;
    G4Exception("CreateGenerator()", "[GeneratorManager]", FatalException, err);
  }

  return p;
}
