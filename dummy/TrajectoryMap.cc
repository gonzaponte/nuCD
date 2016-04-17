// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "TrajectoryMap.hh"

#include <G4VTrajectory.hh>

using namespace nuCD;

std::map<int, G4VTrajectory*> TrajectoryMap::_map;

TrajectoryMap:: TrajectoryMap() {}
TrajectoryMap::~TrajectoryMap() { _map.clear(); }

void TrajectoryMap::Clear() { _map.clear(); }

G4VTrajectory* TrajectoryMap::Get(int trackId)
{
  std::map<int, G4VTrajectory*>::iterator it = _map.find(trackId);
  if (it == _map.end()) return 0;
  else return it->second;
}


