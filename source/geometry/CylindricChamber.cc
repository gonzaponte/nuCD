// ----------------------------------------------------------------------------
//  0
//
//  Author:  Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "geometry/CylindricChamber.hh"

// #include "geometry/sensors/PMT.hh"
//
#include "materials/MaterialsList.hh"
// #include "materials/OpticalMaterialProperties.h"
// #include "physics/RadialEField.h"
// #include "IonizationSD.h"

#include <G4GenericMessenger.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4NistManager.hh>

#include <CLHEP/Units/SystemOfUnits.h>
#include <CLHEP/Units/PhysicalConstants.h>

using namespace CLHEP;
using namespace nuCD;

CylindricChamber:: CylindricChamber(): BaseGeometry(), _msg(0) {SetSize(120*cm);}
CylindricChamber::~CylindricChamber() { delete _msg; }



void CylindricChamber::Construct()
{

 // Chamber design

  const G4double chamber_radius    =  20. * cm;
  const G4double chamber_length    = 100. * cm; // half length
  const G4double chamber_thickness =   1. * cm;

  G4Tubs* chamber_solid = new G4Tubs( "CHAMBER", 0.,
                                      chamber_radius + chamber_thickness,
                                      chamber_length + chamber_thickness,
                                      0., twopi );

  G4LogicalVolume* chamber_logic = new G4LogicalVolume( chamber_solid,
                                                        MaterialsList::Steel(),
                                                        "CHAMBER");

  this->SetLogicalVolume(chamber_logic);


  // Gas design

  G4Tubs* gas_solid = new G4Tubs( "GAS", 0.,
                                  chamber_radius,
                                  chamber_length,
                                  0., twopi );

  // G4Material* gas_mat = MaterialsList::LAr();
  // gas_mat->SetMaterialPropertiesTable( OpticalMaterialProperties::LAr() );
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* gas_mat = nist->FindOrBuildMaterial("G4_LAR");

  G4LogicalVolume* gas_logic = new G4LogicalVolume( gas_solid, gas_mat, "GAS" );

  new G4PVPlacement( 0, G4ThreeVector(), gas_logic, "GAS", chamber_logic, false, 0, true);


  // Active volume

  const G4double active_radius = chamber_radius;
  const G4double active_length = chamber_length; // half length

  G4Tubs* active_solid = new G4Tubs( "ACTIVE", 0.,
                                     active_radius,
                                     active_length,
                                     0, twopi);

  G4LogicalVolume* active_logic = new G4LogicalVolume( active_solid, gas_mat, "ACTIVE" );

  new G4PVPlacement(0, G4ThreeVector(), active_logic, "ACTIVE", gas_logic, false, 0, true);

  // Define this volume as an ionization sensitive detector
  // IonizationSD* sensitive_detector = new IonizationSD("/CYLINDRIC_CHAMBER/ACTIVE");
  // active_logic->SetSensitiveDetector(sensitive_detector);
  // G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector);

  // Define an electric drift field for this volume
  // RadialEField* Efield = new RadialEField();
  // Efield->SetCathodeRadius(0.);
  // Efield->SetAnodeRadius(chamber_radius);
  // Efield->SetDriftVelocity( 1. * mm / microsecond );
  // Efield->SetTransverseDiffusion( 1. * mm / sqrt(cm) );
  // Efield->SetLongitudinalDiffusion( .5 * mm / sqrt(cm) );

  // G4Region* drift_region = new G4Region("DRIFT_REGION");
  // drift_region->SetUserInformation(Efield);
  // drift_region->AddRootLogicalVolume(active_logic);

  // Photomultipliers
  // PMT pmt;
  // pmt.Construct();
  // G4LogicalVolume* pmt_logic = pmt.GetLogicalVolume();
  //
  // new G4PVPlacement( 0, G4ThreeVector(0., 0., -chamber_length), pmt_logic, "PMT", gas_logic, false, 0, true);

}


G4ThreeVector CylindricChamber::GenerateVertex(const G4String&) const{ return G4ThreeVector(); }
