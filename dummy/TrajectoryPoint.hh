// ----------------------------------------------------------------------------
///  \file   TrajectoryPoint.hh
///  \brief  A point (position, time) in the trajectory of a track
/// 
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_TPOINT__
#define __nuCD_TPOINT__

#include <G4VTrajectoryPoint.hh>
#include <G4Allocator.hh>


namespace nuCD
{

  /// A point (position and time) in the trajectory of a simulated track

  class TrajectoryPoint: public G4VTrajectoryPoint
  {
  public:
    TrajectoryPoint();
    TrajectoryPoint(G4ThreeVector, G4double);
    TrajectoryPoint(const TrajectoryPoint&);
    virtual ~TrajectoryPoint();

    const TrajectoryPoint& operator =(const TrajectoryPoint&);
    int operator ==(const TrajectoryPoint&) const;
    void* operator new(size_t);
    void operator delete(void*);

    const G4ThreeVector GetPosition() const;
    G4double GetTime() const;

  private:
    G4ThreeVector _position;
    G4double _time;
}; // class TrajectoryPoint

} // namespace nuCD

#if defined G4TRACKING_ALLOC_EXPORT
extern G4DLLEXPORT G4Allocator<nuCD::TrajectoryPoint> TrjPointAllocator;
#else
extern G4DLLIMPORT G4Allocator<nuCD::TrajectoryPoint> TrjPointAllocator;
#endif

inline int                 nuCD::TrajectoryPoint::operator ==(const TrajectoryPoint& other) const {return (this==&other); }
inline void*               nuCD::TrajectoryPoint::operator new(size_t) { return ((void*) TrjPointAllocator.MallocSingle()); }
inline void                nuCD::TrajectoryPoint::operator delete(void* tp) { TrjPointAllocator.FreeSingle((TrajectoryPoint*) tp); }
inline const G4ThreeVector nuCD::TrajectoryPoint::GetPosition() const { return _position; }
inline G4double            nuCD::TrajectoryPoint::GetTime() const { return _time; }


#endif // __nuCD_TPOINT__