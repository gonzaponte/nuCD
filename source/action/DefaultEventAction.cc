// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "action/DefaultEventAction.hh"
// #include "Trajectory.hh"
#include "core/manager/PersistencyManager.hh"
// #include "IonizationHit.hh"

#include <G4Event.hh>
#include <G4VVisManager.hh>
#include <G4Trajectory.hh>
#include <G4GenericMessenger.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4HCtable.hh>
#include <globals.hh>


using namespace nuCD;


DefaultEventAction::DefaultEventAction(): G4UserEventAction(),
_nevt(0), _nupdate(10), _energy_threshold(0.)
{
  _msg = new G4GenericMessenger(this, "/Actions/Default/");

  G4GenericMessenger::Command& threshold_cmd = _msg->DeclareProperty("energy_threshold", _energy_threshold, "");
    threshold_cmd.SetParameterName("energy_threshold", true);
    threshold_cmd.SetUnitCategory("Energy");
}

DefaultEventAction::~DefaultEventAction() {}

void DefaultEventAction::BeginOfEventAction(const G4Event*)
{
    // Print out event number info
  if (_nevt % _nupdate) return;

  G4cout << " >> Event no. " << _nevt << G4endl;
  if ( _nevt == (10 * _nupdate) ) _nupdate *= 10;
}

void DefaultEventAction::EndOfEventAction(const G4Event* event)
{
  _nevt++;

  if (_energy_threshold < 0.) return;
  // Determine whether total energy deposit in ionization sensitive
  // detectors is above threshold
  G4double edep = 0.;
/*
  // Get the trajectories stored for this event and loop through them
  // to calculate the total energy deposit
  G4TrajectoryContainer* tc = event->GetTrajectoryContainer();
  if (tc)
  {
    for (unsigned int i=0; i<tc->size(); ++i)
    {
      Trajectory* trj = dynamic_cast<Trajectory*>((*tc)[i]);
      edep += trj->GetEnergyDeposit();

      // Draw tracks in visual mode
      if (G4VVisManager::GetConcreteInstance()) trj->DrawTrajectory();
    }
  }
*/
  PersistencyManager* PM = dynamic_cast<PersistencyManager*> (G4VPersistencyManager::GetPersistencyManager());

  // Store the event if the deposited energy is above threshold
  PM->StoreCurrentEvent( (bool) ( edep > _energy_threshold )  );
//  if (edep > _energy_threshold) PM->StoreCurrentEvent(true);
//  else PM->StoreCurrentEvent(false);
}
