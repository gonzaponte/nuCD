// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 23rd 2015
//
// ----------------------------------------------------------------------------

#include "core/manager/GeometryManager.hh"

#include "geometry/BaseGeometry.hh"

#include <G4GenericMessenger.hh>


using namespace nuCD;


GeometryManager::GeometryManager(): _msg(0)
{
  _msg = new G4GenericMessenger(this, "/Geometry/");
  _msg->DeclareProperty("RegisterGeometry", _name, "");
}


GeometryManager::~GeometryManager()
{
  delete _msg;
}


//////////////////////////////////////////////////////////////////////

#include "geometry/CylindricChamber.hh"

BaseGeometry* GeometryManager::CreateGeometry() const
{
  BaseGeometry* p = 0;
  G4cout << "name is " << _name << G4endl;
  if ( _name == "CYLINDRIC_CHAMBER" ) p = new CylindricChamber();
  else
  {
    G4String err = "The user selected an unknown geometry: " + _name;
    G4Exception("CreateGeometry", "[BaseGeometry]", FatalException, err);
  }

  return p;
}
