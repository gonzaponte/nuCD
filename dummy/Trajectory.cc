// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "Trajectory.hh"

#include "TrajectoryPoint.hh"
#include "TrajectoryMap.hh"

#include <G4Track.hh>
#include <G4ParticleDefinition.hh>
#include <G4VProcess.hh>

using namespace nuCD;

G4Allocator<Trajectory> TrjAllocator;

Trajectory::Trajectory(const G4Track* track): 
   G4VTrajectory(),        _pdef(0),       _trackId(-1), _parentId(-1),
  _initial_time(0.),       _final_time(0), _length(0.),   _edep(0.),
  _record_trjpoints(true), _trjpoints(0)
{
  _pdef     = track->GetDefinition();
  _trackID  = track->GetTrackID();
  _parentID = track->GetParentID();

  if (_parentID) _creator_process = track->GetCreatorProcess()->GetProcessName();
  else _creator_process = "none";
    

  _initial_momentum = track->GetMomentum();
  _initial_position = track->GetVertexPosition();
  _initial_time     = track->GetGlobalTime();
  _initial_volume   = track->GetLogicalVolumeAtVertex()->GetName();

  _trjpoints = new TrajectoryPointContainer();

  // Add this trajectory in the map, but only if no other
  // trajectory for this track id has been registered yet
  if (!TrajectoryMap::Get(track->GetTrackID())) TrajectoryMap::Add(this);
}



Trajectory::Trajectory(const Trajectory& other): G4VTrajectory()
{
  _pdef = other._pdef;
}

Trajectory::~Trajectory()
{
  for (unsigned int i=0; i<_trjpoints->size(); i++)
    delete (*_trjpoints)[i];
    
  _trjpoints->clear();
  delete _trjpoints;
}


void Trajectory::AppendStep(const G4Step* step)
{
  if (!_record_trjpoints) return;

  TrajectoryPoint* point = 
    new TrajectoryPoint(step->GetPostStepPoint()->GetPosition(),
                        step->GetPostStepPoint()->GetGlobalTime());
  _trjpoints->push_back(point);
}

void Trajectory::MergeTrajectory(G4VTrajectory* second)
{
  if ( !second || !_record_trjpoints ) return;

  Trajectory* temp = (Trajectory*) second;
  G4int entries = temp->GetPointEntries();

  // initial point of the second trajectory should not be merged
  for (G4int i=1; i<entries ; i++) _trjpoints->push_back((*(tmp->_trjpoints))[i]);

  delete (*tmp->_trjpoints)[0];
  tmp->_trjpoints->clear();
}

void Trajectory::ShowTrajectory(std::ostream& os) const
{
  // Invoke the default implementation
  G4VTrajectory::ShowTrajectory(os);
}

 void Trajectory::DrawTrajectory() const
 {
  // Invoke the default implementation
  G4VTrajectory::DrawTrajectory();
 }

