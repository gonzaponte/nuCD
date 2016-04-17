// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 23rd 2015
//
// ----------------------------------------------------------------------------

#include "core/manager/PersistencyManager.hh"
#include "core/manager/RunManager.hh"

// #include "Trajectory.hh"
// #include "TrajectoryMap.hh"
// #include "IonizationSD.hh"
// #include "PMTSD.hh"

#include <G4GenericMessenger.hh>
#include <G4Event.hh>
#include <G4TrajectoryContainer.hh>
#include <G4Trajectory.hh>
#include <G4SDManager.hh>
#include <G4HCtable.hh>
#include <G4RunManager.hh>

#include <TList.h>

// Event interface
#include <nuEI/Event.hh>
#include <nuEI/Particle.hh>
#include <nuEI/Track.hh>
#include <nuEI/SensorHit.hh>
#include <nuEI/Writer.hh>
//#include <EI/ParameterInfo.h>

#include <string>
#include <sstream>
#include <iostream>

using namespace nuCD;

PersistencyManager::PersistencyManager():
  G4VPersistencyManager(), _msg(0), _historyFile("G4history.macro"),
  _ready(false), _store_evt(true),  _evt(0), _writer(0)
{
  _msg = new G4GenericMessenger(this, "/persistency/");
  _msg->DeclareMethod("outputFile", &PersistencyManager::OpenFile, "");
  _msg->DeclareProperty("historyFile", _historyFile, "Name of the file where the configuration information are stored");
}

PersistencyManager::~PersistencyManager()
{
  delete _writer;
  delete _msg;
}

void PersistencyManager::Initialize()
{
  // Get a pointer to the current singleton instance of the persistency
  // manager using the method of the base class
  PersistencyManager* current = dynamic_cast<PersistencyManager*> (G4VPersistencyManager::GetPersistencyManager());

  // If no instance exists yet, create a new one.
  // (Notice that the above dynamic cast would also return 0 if an instance
  // of another G4VPersistencyManager-derived was previously set, resulting
  // in the leak of that object since the pointer will no longer be
  // accessible.)
  if (!current) current = new PersistencyManager();
}

void PersistencyManager::OpenFile(const G4String& filename)
{
  if (_ready) // Some file has been already opened
    G4Exception("OpenFile()", "[PersistencyManager]", JustWarning, "An output file was previously opened.");
  else // If the output file was not set yet, do so
  {
    _writer = new nuEI::Writer();
    _ready = (G4bool) _writer->Open(filename.data(), "RECREATE");

    if (!_ready)
      G4Exception("OpenFile()", "[PersistencyManager]", FatalException, "The path for the output file does not exist.");
  }
}

void PersistencyManager::CloseFile()
{
  if (!_writer || !_writer->IsOpen()) return;

  _writer->Close();
}

G4bool PersistencyManager::Store(const G4Event* event)
{
  if (!_store_evt)
  {
    // TrajectoryMap::Clear();
    return false;
  }

  // Create a new nuEI event
  nuEI::Event ievt(event->GetEventID());

  // Store the trajectories of the event as nuEI particles
  // StoreTrajectories(event->GetTrajectoryContainer(), &ievt);
  //
  // StoreHits(event->GetHCofThisEvent(), &ievt);


  // Add event to the tree
  _writer->Write(ievt);

  // TrajectoryMap::Clear();
  StoreCurrentEvent(true);

  return true;
}

G4bool PersistencyManager::Store(const G4Run*){return true;}

/*
void PersistencyManager::StoreTrajectories(G4TrajectoryContainer* tc, nuEI::Event* ievent)
{
  // If the pointer is null, no trajectories were stored in this event
  if (!tc) return;

  // Reset the map of nuEI::Particles
  _particle_map.clear();

  // Loop through the trajectories stored in the container
  for (G4int i=0; i<tc->entries(); i++)
  {
    Trajectory* trj = dynamic_cast<Trajectory*>((*tc)[i]);
    if (!trj) continue;

    // Create an nuEI particle to store the trajectory information
    nuEI::Particle* ipart = new nuEI::Particle(trj->GetPDGEncoding());

    G4int trackID = trj->GetTrackID();
    ipart->SetParticleID(trackID);
    _particle_map[trackID] = ipart;

    G4double tracklength = trj->GetTrackLength();
    ipart->SetTrackLength(tracklength);

    G4ThreeVector xyz = trj->GetInitialPosition();
    G4double t = trj->GetInitialTime();
    ipart->SetInitialVertex( xyz.x(), xyz.y(), xyz.z(), t );

    xyz = trj->GetFinalPosition();
    t = trj->GetFinalTime();
    ipart->SetDecayVertex( xyz.x(), xyz.y(), xyz.z(), t );

    G4String volume = trj->GetInitialVolume();
    ipart->SetInitialVolume(volume);

    volume = trj->GetDecayVolume();
    ipart->SetDecayVolume(volume);

    G4double mass = trj->GetParticleDefinition()->GetPDGMass();
    G4ThreeVector mom = trj->GetInitialMomentum();
    G4double energy = sqrt( mom.mag2() + mass*mass );
    ipart->SetInitialMomentum( mom.x(), mom.y(), mom.z(), energy );

    ievent->AddParticle(ipart);
  }

  // Set family relationships.
  // Loop through the particles we just stored in the nuEI event.
  TObjArray* iparts = ievent->GetParticles();
  for (G4int i=0; i<iparts->GetEntries(); i++)
  {
    nuEI::Particle* ipart = (nuEI::Particle*) iparts->At(i);
    Trajectory* trj = (Trajectory*) TrajectoryMap::Get(ipart->GetParticleID());
    int parentID = trj->GetParentID();
    ipart->SetCreatorProcess(trj->GetCreatorProcess());

    if (!parentID)
      ipart->SetPrimary(true);

    else
    {
      nuEI::Particle* mother = _particle_map[parentID];
      ipart->SetPrimary(false);
      ipart->SetMother(mother);
      mother->AddDaughter(ipart);
    }
  }
}

void PersistencyManager::StoreHits(G4HCofThisEvent* HC, nuEI::Event* ievt)
{
  if (!hce) return;

  G4SDManager* SD = G4SDManager::GetSDMpointer();
  G4HCtable*  HCT = SD->GetHCtable();

  // Loop through the hits collections
  for (int i=0; i<hct->entries(); i++)
  {
    // Collection are identified univocally (in principle) using
    // their id number, and this can be obtained using the collection
    // and sensitive detector names.
    G4String HCname = HCT->GetHCname(i);
    G4String SDname = HCT->GetSDname(i);
    int hcID = SD->GetCollectionID(SDname+"/"+HCname);

    // Fetch collection using the id number
    G4VHitsCollection* hits = HC->GetHC(hcID);

    if (HCname == IonizationSD::GetCollectionUniqueName()) StoreIonizationHits(hits, ievt);
    else if (HCname == PMTSD::GetCollectionUniqueName()) StorePMTHits(hits, ievt);
    else
    {
      G4String msg = "Collection of hits '" + SDname + "/" + HCname + "' is of an unknown type and will not be stored.";
      G4Exception("StoreHits()", "[PersistencyManager]", JustWarning, msg);
      return;
    }
  }
}

void PersistencyManager::StoreIonizationHits(G4VHitsCollection* HC, nuEI::Event* ievt)
{
  IonizationHitsCollection* hits = dynamic_cast<IonizationHitsCollection*>(HC);
  if (!hits) return;

  _track_map.clear();

  for (G4int i=0; i<hits->entries(); i++)
  {
    IonizationHit* hit = dynamic_cast<IonizationHit*>(hits->GetHit(i));
    if (!hit) continue;

    G4int trackID = hit->GetTrackID();

    nuEI::Track* itrk = 0;

    std::map<G4int, nuEI::Track*>::iterator it = _track_map.find(trackID);

    if (it != _itrkmap.end())
      itrk = it->second;

    else
    {
      std::string SDname = hits->GetSDname();
      itrk = new nuEI::Track(SDname);
      _track_map[trackID] = itrk;
      itrk->SetParticle(_particle_map[trackID]);
      _particle_map[trackID]->AddTrack(itrk);
      ievt->AddTrack(itrk);
    }

    G4ThreeVector xyz = hit->GetPosition();
    itrk->AddHit( xyz.x(), xyz.y(), xyz.z(), hit->GetTime(), hit->GetEnergyDeposit());
  }
  return;
}

void PersistencyManager::StorePMTHits(G4VHitsCollection* HC, nuEI::Event* ievt )
{
  PMTHitsCollection* hits = dynamic_cast<PMTHitsCollection*>(HC);
  if (!hits) return;

  for (G4int i=0; i<hits->entries(); i++)
  {
    PMTHit* hit = dynamic_cast<PMTHit*>(hits->GetHit(i));
    if (!hit) continue;

    std::string SDname = hits->GetSDname();
    nuEI::SensorHit* isensor = new nuEI::SensorHit(SDname);

    isensor->SetID(hit->GetPMTID());
    isensor->SetBinWidth(hit->GetBinSize());

    G4ThreeVector xyz = hit->GetPosition();
    isensor->SetPosition( xyz.x(), xyz.y(), xyz.z() );

    const std::map<G4double, G4int>& waveform = hit->GetHistogram();
    std::map<G4double, G4int>::const_iterator it;

    G4double amplitude = 0.;
    for (it = waveform.begin(); it != waveform.end(); it++)
    {
      isensor->SetSample( it->second, it->first );
      amplitude += it->second;
    }
    isensor->SetAmplitude(amplitude);

    // Add the sensor hit to the nuEI event
    ievt->AddSensorHit(isensor);
  }
  return;
}

G4bool PersistencyManager::Store(const G4Run*)
{
  std::ifstream history(_historyFile, std::ifstream::in);

  while (history.good())
  {
    std::string key, value;
    std::getline(history, key, ' ');
    std::getline(history, value);

    if (key != "")
    {
      nuEI::ParameterInfo* info = new nuEI::ParameterInfo(key.c_str());
      info->SetContent(value);
      _writer->WriteMetadata(info);
    }
  }

  history.close();

  // Store the number of events to be processed
  RunManager* RM = (RunManager*) G4RunManager::GetRunManager();
  G4int Nevents = RM->GetNumberOfEventsToBeProcessed();

  std::stringstream ss;
  ss << Nevents;

  nuEI::ParameterInfo* info = new nuEI::ParameterInfo("Nevents");
  info->SetContent(ss.str());
  _writer->WriteMetadata(info);

  return true;
}
*/
