
// ----------------------------------------------------------------------------
//  $Id: Track.cc 9821 2014-04-25 18:59:18Z gomez $
//
//  Author:  <paola.ferrario@ific.uv.es>
//  Created: 14 Feb 2013
//
//  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#include "Track.hh"
#include "Particle.hh"
#include "Units.hh"

ClassImp(nuEI::Track)

namespace nuEI
{

  Track::Track() :
  _particle(0), _detector_name("Unknown"),_hits()
  {  }

  Track::Track(std::string& detector) :
    _particle(0), _detector_name(detector),_hits()
  {  }

  void Track::SetParticle(Particle* particle)
  {
     _particle = particle;
  }
  const Particle* Track::GetParticle() const
  {
    if (!_particle.GetObject())
      std::cerr << "======================================== "
                << "Error in nuEI::Track::GetParticle():     "
    		        << "The is no particle related to this track "
                << "======================================== " << std::endl;
    return dynamic_cast<Particle*> (_particle.GetObject());
  }

  void Track::Info(std::ostream& s) const
  {
    s << "Total number of hits:  " << _hits.size() << std::endl;
    for (int i=0; i<_hits.size(); ++i)
    {
      std::pair<TLorentzVector,double> hit = _hits[i];
      s  << "- - - - - - - - - " << i << " - - - - - - - - - - " << std::endl
         << "Hit position (mm):     " << hit.first.X()/mm << " " << hit.first.Y()/mm << " " << hit.first.Z()/mm << std::endl
         << "Time:                  " << hit.first.T()/second << std::endl
         << "Deposited energy:      " << hit.second << std::endl;
    }
  }

}  // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::Track& track) {
  track.Info(s);
  return s;
}
