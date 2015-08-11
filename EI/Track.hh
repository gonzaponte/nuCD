///////////////////////////////////////////////////////////////////////////////
////
////  Class that contains topological information and energy depositions
////  produced by some particle.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_TRACK__
#define __nuEI_TRACK__

#include <TObject.h>
#include <TLorentzVector.h>
#include <TRef.h>
#include <vector>
#include <utility>
#include <iostream>

namespace nuEI {class Particle;}

namespace nuEI
{

  class Track: public TObject
  {

  public:
    // Empty constructor
    Track();
    // Naming constructor
    Track(std::string& detector);
    /// Destructor
    ~Track(){ }

  private:
    std::vector<std::pair<TLorentzVector,double> > _hits; // true hits in the track: a pair of a TLorentzVector that contains the position and the time of the hit and a double for energy deposition.
    TRef        _particle;                                // reference to the particle that has created this track
    std::string _detector_name;                           // detector where hits have been produced

  public:
    void AddHit(double x, double y, double z, double t, double e);
    void AddHit(TLorentzVector V, double energy);
    const std::vector<std::pair<TLorentzVector,double> >& GetHits() const;

    void SetParticle(Particle* particle);
    const Particle* GetParticle() const;

    void SetDetectorName(const std::string& det);
    const std::string& GetDetectorName() const;

    void Info(std::ostream& s) const;

    ClassDef(Track,1);

  };

  // INLINE methods
  inline void Track::AddHit(double x, double y, double z, double t, double e){ TLorentzVector V(x,y,z,t); AddHit(V,e); }
  inline void Track::AddHit(TLorentzVector V, double e){ std::pair<TLorentzVector,double> pair( V, e ); _hits.push_back( pair );}
  inline const std::vector<std::pair<TLorentzVector,double> >& Track::GetHits() const{ return _hits;}
  inline void Track::SetDetectorName(const std::string& det) {_detector_name = det;}
  inline const std::string& Track::GetDetectorName() const {return _detector_name;}

} // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::Track& tr);

#endif // __nuEI_TRACK__
