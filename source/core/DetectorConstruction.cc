///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "core/DetectorConstruction.hh"

#include "geometry/BaseGeometry.hh"

#include <G4Box.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>


namespace nuCD
{

  DetectorConstruction::DetectorConstruction() :
  _geometry(0) { }

  DetectorConstruction::~DetectorConstruction()
  {
    delete _geometry;
  }

  G4VPhysicalVolume* DetectorConstruction::Construct()
  {
    // Check whether a detector geometry has been set or not
    if (!_geometry)
      G4Exception("Construct()", "[DetectorConstruction]", FatalException, "Geometry 5not set!");

    _geometry->Construct();

    // The world volume is a huge empty box
    G4double Wsize     = _geometry->GetSize() * 0.5; // * 0.5 -> half size
    G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

    G4Box*           Wsolid = new G4Box( "WORLD", Wsize, Wsize, Wsize);
    G4LogicalVolume* Wlogic = new G4LogicalVolume( Wsolid, vacuum, "WORLD", 0, 0, 0, true );
    G4PVPlacement*   Wphys  = new G4PVPlacement( 0, G4ThreeVector(), Wlogic, "WORLD", 0, false, 0);

    // User's geometry goes in the center
    G4LogicalVolume* Glogic = _geometry->GetLogicalVolume();
    new G4PVPlacement(0, G4ThreeVector(), Glogic, Glogic->GetName(), Wlogic, false, 0);

    // visualisation stuff
    Wlogic->SetVisAttributes(G4VisAttributes::Invisible);

    return Wphys;
  }

}
