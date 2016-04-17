///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "core/manager/RunManager.hh"
#include "core/manager/GeometryManager.hh"
#include "core/manager/GeneratorManager.hh"
#include "core/manager/ActionsManager.hh"
#include "core/manager/PersistencyManager.hh"

#include "core/DetectorConstruction.hh"
#include "core/PrimaryGeneration.hh"
#include "core/BatchSession.hh"

#include <G4GenericPhysicsList.hh>
#include <G4UImanager.hh>
#include <G4StateManager.hh>

namespace nuCD{

  RunManager::RunManager(G4String init_macro):
  G4RunManager(), _historyFile("history.txt")
  {
    _msg = new G4GenericMessenger(this, "/nucd/", "nuCD control commands.");

    _msg->DeclareMethod("RegisterMacro", &RunManager::RegisterMacro, "");
    _msg->DeclareMethod("RegisterDelayedMacro", &RunManager::RegisterDelayedMacro, "");
    _msg->DeclareMethod("random_seed", &RunManager::SetRNGseed, "Set a seed for the random number generator.");
    _msg->DeclareProperty("historyFile", _historyFile, "Set the name of the file to store executed commands.");

    /////////////////////////////////////////////////////////

    // We will set now the user initialization class instances
    // in the run manager. In order to do so, we create first the factories
    // (the objects that construct the appropriate instances according
    // to user's input) so that the messenger commands are already defined
    // by the time we process the initialization macro.

    GeometryManager  geoMan;
    GeneratorManager genMan;
    ActionsManager    actMan;

    // The physics lists are handled with Geant4's own 'Manager'
    physicsList = new G4GenericPhysicsList();

    // Process now the initialization macro
    BatchSession* batch = new BatchSession(init_macro.c_str());
    batch->SessionStart();

    // Set the physics list in the run manager
    this->SetUserInitialization(physicsList);

    // Set the detector construction instance in the run manager
    DetectorConstruction* detCon = new DetectorConstruction();
    detCon->SetGeometry( geoMan.CreateGeometry() );
    this->SetUserInitialization(detCon);

    // Set the primary generation instance in the run manager
    PrimaryGeneration* primGen = new PrimaryGeneration();
    primGen->SetGenerator( genMan.CreateGenerator() );
    this->SetUserAction(primGen);

    // Set the user action instances, if any, in the run manager

    G4UImanager* UI = G4UImanager::GetUIpointer();

    if (UI->GetCurrentValues("/Actions/RegisterRunAction") != "")
      this->SetUserAction( actMan.CreateRunAction() );

    if (UI->GetCurrentValues("/Actions/RegisterEventAction") != "")
      this->SetUserAction( actMan.CreateEventAction() );

    if (UI->GetCurrentValues("/Actions/RegisterStackingAction") != "")
      this->SetUserAction( actMan.CreateStackingAction() );

    if (UI->GetCurrentValues("/Actions/RegisterTrackingAction") != "")
      this->SetUserAction( actMan.CreateTrackingAction() );

    if (UI->GetCurrentValues("/Actions/RegisterSteppingAction") != "")
      this->SetUserAction( actMan.CreateSteppingAction() );

    UI->StoreHistory( _historyFile.c_str() );

    SetRNGseed(0);

    PersistencyManager::Initialize();
  }

  RunManager::~RunManager()
  {
    PersistencyManager* PM = dynamic_cast<PersistencyManager*> ( G4VPersistencyManager::GetPersistencyManager() );
    PM->CloseFile();
    delete _msg;
  }

  void RunManager::Initialize()
  {
    for (unsigned int i=0; i< _macros.size(); i++) ExecuteMacroFile( _macros[i].data());
    G4RunManager::Initialize();
    for (unsigned int j=0; j<_delayed.size(); j++) ExecuteMacroFile(_delayed[j].data());
  }

  void RunManager::ExecuteMacroFile(const char* filename)
  {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    G4UIsession* BS = new BatchSession(filename, UI->GetSession());
    UI->SetSession(BS);
    G4UIsession* pUI = UI->GetSession()->SessionStart();
    delete UI->GetSession();
    UI->SetSession(pUI);
  }

  void RunManager::SetRNGseed(G4int seed)
  {
    G4int SEED = (seed>0) ? seed : time(0);
    CLHEP::HepRandom::setTheSeed(SEED);
  }


} // namespace nuCD
