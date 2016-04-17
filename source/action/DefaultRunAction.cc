// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "action/DefaultRunAction.hh"

#include <G4Run.hh>

using namespace nuCD;

DefaultRunAction:: DefaultRunAction(): G4UserRunAction() {}
DefaultRunAction::~DefaultRunAction() {}

void DefaultRunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
}

void DefaultRunAction::EndOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " end." << G4endl;
}
