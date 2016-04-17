// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martinez Lema
//  Created: May 17th 2015
//
// ----------------------------------------------------------------------------

#include "core/manager/ActionsManager.hh"

#include <G4GenericMessenger.hh>
#include <G4UserRunAction.hh>
#include <G4UserEventAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>
#include <G4UserStackingAction.hh>

using namespace nuCD;


ActionsManager::ActionsManager(): _msg(0)
{
  _msg = new G4GenericMessenger(this, "/Actions/");
  _msg->DeclareProperty("RegisterRunAction",      _RA_name, "");
  _msg->DeclareProperty("RegisterEventAction",    _EA_name, "");
  _msg->DeclareProperty("RegisterTrackingAction", _TA_name, "");
  _msg->DeclareProperty("RegisterSteppingAction", _SPA_name, "");
  _msg->DeclareProperty("RegisterStackingAction", _STA_name, "");
}


ActionsManager::~ActionsManager()
{
  delete _msg;
}


//////////////////////////////////////////////////////////////////////
#include "action/DefaultRunAction.hh"

G4UserRunAction* ActionsManager::CreateRunAction() const
{
  G4UserRunAction* RA = 0;
  if (_RA_name == "DEFAULT") RA =  new DefaultRunAction();
  else
  {
    G4String err = "Unknown user run action: " + _RA_name;
    G4Exception("CreateRunAction()", "[ActionsManager]", JustWarning, err);
  }
  return RA;
}


//////////////////////////////////////////////////////////////////////
#include "action/DefaultEventAction.hh"

G4UserEventAction* ActionsManager::CreateEventAction() const
{
  G4UserEventAction* EA = 0;
  if (_EA_name == "DEFAULT") EA = new DefaultEventAction();
  else
  {
    G4String err = "Unknown user event action: " + _EA_name;
    G4Exception("CreateEventAction()", "[ActionsManager]", JustWarning, err);
  }
  return EA;
}


//////////////////////////////////////////////////////////////////////
#include "action/DefaultTrackingAction.hh"

G4UserTrackingAction* ActionsManager::CreateTrackingAction() const
{
  G4UserTrackingAction* TA = 0;
  if (_TA_name == "DEFAULT") TA = new DefaultTrackingAction();
  else
  {
    G4String err = "Unknown user tracking action: " + _TA_name;
    G4Exception("CreateTrackingAction()", "[ActionsManager]", JustWarning, err);
  }
  return TA;
}


//////////////////////////////////////////////////////////////////////
#include "action/DefaultSteppingAction.hh"

G4UserSteppingAction* ActionsManager::CreateSteppingAction() const
{
  G4UserSteppingAction* SPA = 0;
  if (_SPA_name == "DEFAULT") SPA = new DefaultSteppingAction();
  else
  {
    G4String err = "Unknown user stepping action: " + _SPA_name;
    G4Exception("CreateSteppingAction()", "[ActionsManager]", JustWarning, err);
  }
  return SPA;
}


//////////////////////////////////////////////////////////////////////
#include "action/DefaultStackingAction.hh"

G4UserStackingAction* ActionsManager::CreateStackingAction() const
{
  G4UserStackingAction* STA = 0;
  if (_STA_name == "DEFAULT") STA = new DefaultStackingAction();
  else
  {
    G4String err = "Unknown user stacking action: " + _STA_name;
    G4Exception("CreateStackingAction()", "[ActionsManager]", JustWarning, err);
  }
  return STA;
}
