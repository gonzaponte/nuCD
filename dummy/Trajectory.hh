// ----------------------------------------------------------------------------
///  \file   Trajectory.h
///  \brief  Record of a track used by the persistency mechanism.
/// 
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_TRAJECTORY__
#define __nuCD_TRAJECTORY__

#include <G4VTrajectory.hh>
#include <G4Allocator.hh>

class G4Track;
class G4ParticleDefinition;
class G4VTrajectoryPoint;


namespace nuCD
{
  typedef std::vector<G4VTrajectoryPoint*> TrajectoryPointContainer;


  /// Record of a track used by the persistency mechanism. 
  /// It stores basic information of the particle and its path through 
  /// the geometry. A number of its properties are copied from the track
  /// in construction and cannot be modified.

  class Trajectory: public G4VTrajectory
  {
  public:
    Trajectory(const G4Track*);
    Trajectory(const Trajectory&);
    virtual ~Trajectory();

    /// Memory allocation operator
    void* operator new(size_t);
    /// Memory deallocation operator
    void operator delete(void*);
    /// Equality operator
    int operator ==(const Trajectory&) const;

  public:
    // Getters
    G4ParticleDefinition* GetParticleDefinition();
    G4String              GetParticleName() const;
    G4double              GetCharge() const;
    G4int                 GetPDGEncoding () const;
    G4String              GetCreatorProcess() const;
    G4int                 GetTrackID() const;
    G4int                 GetParentID() const;
    G4ThreeVector         GetInitialMomentum() const;
    G4ThreeVector         GetInitialPosition() const;
    G4double              GetInitialTime() const;
    G4double              GetFinalTime() const;
    G4ThreeVector         GetFinalPosition() const;
    G4double              GetTrackLength() const;
    G4double              GetEnergyDeposit() const;
    G4String              GetInitialVolume() const;
    G4String              GetDecayVolume() const;

    // Setters
    void SetFinalPosition(const G4ThreeVector&);
    void SetFinalTime(G4double);
    void SetTrackLength(G4double);
    void SetEnergyDeposit(G4double);
    void SetDecayVolume(G4String);

    
    /// Return the number of trajectory points
    virtual int GetPointEntries() const;
    /// Return the i-th point in the trajectory
    virtual G4VTrajectoryPoint* GetPoint(G4int i) const;
    virtual void AppendStep(const G4Step*);
    virtual void MergeTrajectory(G4VTrajectory*);
    virtual void ShowTrajectory(std::ostream&) const;
    virtual void DrawTrajectory() const;

  private:
    /// The default constructor is private. A trajectory can
    /// only be constructed associated to a track.
    Trajectory();
 
  private:
    G4ParticleDefinition*     _pdef;
    G4int                     _trackID;
    G4int                     _parentID;
    G4ThreeVector             _initial_momentum;
    G4ThreeVector             _initial_position;
    G4ThreeVector             _final_position;
    G4double                  _initial_time;
    G4double                  _final_time;
    G4double                  _length;
    G4double                  _edep;
    G4String                  _creator_process;
    G4String                  _initial_volume;
    G4String                  _decay_volume;
    G4bool                    _record_trjpoints;
    TrajectoryPointContainer* _trjpoints;

}; // class Trajectory

} // namespace nuCD


#ifdef G4TRACKING_ALLOC_EXPORT
extern G4DLLEXPORT G4Allocator<nuCD::Trajectory> TrjAllocator;
#else
extern G4DLLIMPORT G4Allocator<nuCD::Trajectory> TrjAllocator;
#endif

inline void* nuCD::Trajectory::operator new(size_t) { return ((void*) TrjAllocator.MallocSingle()); }
inline void  nuCD::Trajectory::operator delete(void* trj) { TrjAllocator.FreeSingle((nuCD::Trajectory*) trj); }

inline G4ParticleDefinition* nuCD::Trajectory::GetParticleDefinition() { return _pdef; }
inline int                   nuCD::Trajectory::GetPointEntries() const { return _trjpoints->size(); }
inline G4VTrajectoryPoint*   nuCD::Trajectory::GetPoint(G4int i) const { return (*_trjpoints)[i]; }

inline G4ThreeVector nuCD::Trajectory::GetInitialMomentum() const { return _initial_momentum; }
inline G4int         nuCD::Trajectory::GetTrackID() const { return _trackID; }
inline G4int         nuCD::Trajectory::GetParentID() const { return _parentID; }
inline G4ThreeVector nuCD::Trajectory::GetInitialPosition() const { return _initial_position; }
inline G4ThreeVector nuCD::Trajectory::GetFinalPosition() const { return _final_position; }
inline G4double      nuCD::Trajectory::GetInitialTime() const { return _initial_time; }
inline G4double      nuCD::Trajectory::GetFinalTime() const { return _final_time; }
inline void          nuCD::Trajectory::SetFinalTime(G4double t) { _final_time = t; }
inline G4double      nuCD::Trajectory::GetTrackLength() const { return _length; }
inline G4double      nuCD::Trajectory::GetEnergyDeposit() const { return _edep; }
inline G4String      nuCD::Trajectory::GetCreatorProcess() const { return _creator_process; }
inline G4String      nuCD::Trajectory::GetInitialVolume() const { return _initial_volume; }
inline G4String      nuCD::Trajectory::GetDecayVolume() const { return _decay_volume; }
inline G4String      nuCD::Trajectory::GetParticleName() const { return _pdef->GetParticleName(); }
inline G4int         nuCD::Trajectory::GetPDGEncoding() const { return _pdef->GetPDGEncoding(); }
inline G4double      nuCD::Trajectory::GetCharge() const { return _pdef->GetPDGCharge(); }


inline void nuCD::Trajectory::SetFinalPosition(const G4ThreeVector& x) { _final_position = x; }
inline void nuCD::Trajectory::SetTrackLength(G4double l) { _length = l; }
inline void nuCD::Trajectory::SetEnergyDeposit(G4double e) { _edep = e; }
inline void nuCD::Trajectory::SetDecayVolume(G4String dv) { _decay_volume = dv; }

#endif  // __nuCD_TRAJECTORY__
