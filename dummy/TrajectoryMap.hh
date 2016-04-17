// ----------------------------------------------------------------------------
///  \file   TrajectoryMap.hh
///  \brief  
///  
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_TMAP__
#define __nuCD_TMAP__

#include <map>

class G4VTrajectory;


namespace nuCD
{
  class TrajectoryMap
  {
  public:
    /// Return a trajectory given its track ID
    static G4VTrajectory* Get(int trackId);
    /// Add a trajectory to the map
    static void Add(G4VTrajectory*);
    /// Clear the map
    static void Clear();

  private:
    // Constructors, destructor and assignement op are hidden
    // so that no instance of the class can be created.
     TrajectoryMap();
     TrajectoryMap(const TrajectoryMap&);
    ~TrajectoryMap();

    static std::map<int, G4VTrajectory*> _map;
  }; // class TrajectoryMap

  inline void TrajectoryMap::Add(G4VTrajectory* trj) { _map[trj->GetTrackID()] = trj; }
    
} // namespace nuCD


#endif // __nuCD_TMAP__

