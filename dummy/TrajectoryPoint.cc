// ----------------------------------------------------------------------------
//  0
//
//  Author : Gonzalo Martínez Lema
//  Created: May 24th 2015
//
// ----------------------------------------------------------------------------

#include "TrajectoryPoint.hh"

using namespace nuCD;

G4Allocator<TrajectoryPoint> TrjPointAllocator;


TrajectoryPoint:: TrajectoryPoint(): _position(0.,0.,0.), _time(0.) {}
TrajectoryPoint:: TrajectoryPoint(G4ThreeVector pos, G4double t): _position(pos), _time(t) {}
TrajectoryPoint:: TrajectoryPoint(const TrajectoryPoint& other) { *this = other; }
TrajectoryPoint::~TrajectoryPoint(){}

const TrajectoryPoint& TrajectoryPoint::operator=(const TrajectoryPoint& other)
{
  _position = other._position;
  _time     = other._time;

  return *this;
}

