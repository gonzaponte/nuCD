// ----------------------------------------------------------------------------
///  \file   PersistencyManager.hh
///  \brief
///
///  \author   Gonzalo Martínez Lema
///  \date     May 23rd 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_PM__
#define __nuCD_PM__

#include <G4VPersistencyManager.hh>
#include <map>

class G4GenericMessenger;
class G4TrajectoryContainer;
class G4HCofThisEvent;
class G4VHitsCollection;

namespace nuEI
{
    class Event;
    class Particle;
    class Track;
    class Writer;
}

namespace nuCD
{
  class PersistencyManager: public G4VPersistencyManager
  {
  public:
    /// Create the singleton instance of the persistency manager
    static void Initialize();

    /// Set whether to store or not the current event
    void StoreCurrentEvent(G4bool);

    ///
    virtual G4bool Store(const G4Event*);
    virtual G4bool Store(const G4Run*);
    virtual G4bool Store(const G4VPhysicalVolume*);

    virtual G4bool Retrieve(G4Event*&);
    virtual G4bool Retrieve(G4Run*&);
    virtual G4bool Retrieve(G4VPhysicalVolume*&);

    void OpenFile(const G4String&);
    void CloseFile();


  private:
     PersistencyManager();
     PersistencyManager(const PersistencyManager&);
    ~PersistencyManager();


    void StoreTrajectories(G4TrajectoryContainer*, nuEI::Event*);
    void StoreHits(G4HCofThisEvent*, nuEI::Event*);
    void StoreIonizationHits(G4VHitsCollection*, nuEI::Event*);
    void StorePMTHits(G4VHitsCollection*, nuEI::Event*);


  private:
    G4GenericMessenger* _msg; ///< User configuration messenger

    G4String _historyFile;

    G4bool _ready;     ///< Is the PersistencyManager ready to go?
    G4bool _store_evt; ///< Should we store the current event?

    nuEI::Event*  _evt;    ///< Persistent nuEI event
    nuEI::Writer* _writer; ///< Event writer

    std::map<G4int, nuEI::Particle*> _particle_map;
    std::map<G4int, nuEI::Track*   > _track_map;
  }; // class PersistencyManager

  inline void PersistencyManager::StoreCurrentEvent(G4bool sce)     { _store_evt = sce; }
  inline G4bool PersistencyManager::Store(const G4VPhysicalVolume*) { return false; }
  inline G4bool PersistencyManager::Retrieve(G4Event*&)             { return false; }
  inline G4bool PersistencyManager::Retrieve(G4Run*&)               { return false; }
  inline G4bool PersistencyManager::Retrieve(G4VPhysicalVolume*&)   { return false; }

} // namespace nuCD

#endif // __nuCD_PM__
