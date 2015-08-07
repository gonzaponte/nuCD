///////////////////////////////////////////////////////////////////////////////
////
////  Structure of an event in nuCD. Contains all the information.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     07/08/2015
////  @Mofidied 07/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_EVENT__
#define __nuEI_EVENT__

#include <iostream>
#include <string>
#include <vector>

#include <TObject.h>
#include <TObjArray.h>

namespace nuEI
{
class SensorHit;
class Track;
class Particle;
}

namespace nuEI
{
  class Event : public TObject
  {

  public:
    // Constructor
    Event();
    // Evt-ID-numbered constructor
    Event(int id);
    // Copy Constructor
    Event(const Event& right);
    // Destructor
    ~Event();

  private:

    TObjArray* _sensor_hits; // sensor response
    TObjArray* _tracks;      // true hits of particles
    TObjArray* _particles;   // particles
    int        _eventID;     // event identificative number (unique)

  public:

    Event& operator=(const Event& right);

    void AddSensorHit(SensorHit* hit);
    const TObjArray* GetSensorHits() const;

    void AddTrack(Track* track);
    const TObjArray* GetTracks() const;
    std::vector<const nuEI::Track*> Tracks(std::string sensorname = "") const;

    void AddParticle(Particle* particle);
          TObjArray* GetParticles();
    const TObjArray* GetParticles() const;
    std::vector<const nuEI::Particle*> Particles() const;

    void SetID(int id);
    int GetID() const;

    void Clear();
    void Info(ostream& s) const;

    ClassDef(Event,1);

  };

  // INLINE methods
  inline const TObjArray* Event::GetSensorHits() const {return _sensor_hits;}
  inline const TObjArray* Event::GetTracks() const {return _tracks;}
  inline const TObjArray* Event::GetParticles() const {return _particles;}
  inline       TObjArray* Event::GetParticles() {return _particles;}
  inline             void Event::SetID(int id) {_eventID = id;}
  inline              int Event::GetID() const {return _eventID;}

} // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::Event& ev);

#endif // __nuEI_EVENT__
