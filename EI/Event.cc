///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "Event.hh"

ClassImp(nuEI::Event)

namespace nuEI
{
  // Empty constructor
  Event::Event() : _eventID(-1), _sensor_hits(0), _tracks(0), _particles(0) {}

  // Evt-ID-numbered constructor
  Event::Event(int id) : _eventID(id)
  {
    _sensor_hits = new TObjArray();
    _tracks      = new TObjArray();
    _particles   = new TObjArray();
  }

  // Copy constructor
  Event::Event(const Event& right)
  {
    *this = right;
  }

  // Assigment
  Event& Event::operator=(const Event& right)
  {
    if (this != &right)
    {
      _sensor_hits = (TObjArray*) right.GetSensorHits()->Clone();
      _tracks      = (TObjArray*) right.GetTracks()->Clone();
      _particles   = (TObjArray*) right.GetParticles()->Clone();

      _eventID = right.GetID();
    }
    return *this;
  }

  // Destructor
  Event::~Event()
  {
    this->Clear();
    delete _sensor_hits;
    delete _tracks;
    delete _particles;
  }

  void Event::Clear()
  {
    if (_sensor_hits) _sensor_hits->Delete();
    if (_tracks)      _tracks->Delete();
    if (_particles)   _particles->Delete();
    _eventID = -1;
  }

  std::vector<const nuEI::Track*> Event::Tracks( std::string sensorname ) const
  {
    std::vector<const Track*> tracks;
    bool no_filter = !(sensorname == "");//(bool)std::strcmp(sensorname,"");
    for (int it = 0; it <= (int)_tracks->GetLast(); ++it)
    {
      const Track* track = dynamic_cast<const Track*> (_tracks->At(it));
      if ( no_filter || ( track->GetDetectorName() == sensorname ) ) tracks.push_back(track);
    }
    return tracks;
  }

  std::vector<const nuEI::Particle*> Event::Particles() const
  {
    std::vector<const Particle*> particles;
    for (int it = 0; it <= (int)_particles->GetLast(); ++it)
    {
      const Particle* particle = dynamic_cast<const Particle*> (_particles->At(it)) ;
      particles.push_back(particle);
    }
    return particles;
  }

  void Event::Info(std::ostream& s) const
  {
    s << std::endl
      << "Event number:         " << _eventID << std::endl;

    int Nhits=0;
    for ( int it=0; it<=(int)_tracks->GetLast(); ++it)
    {
      Track* track = (Track*) _tracks->At(it);
      Nhits += track->GetHits().size();
    }

    s << "Number of true hits:  " << Nhits                     << std::endl;
    s << "Number of sensor hits " << _sensor_hits->GetLast()+1 << std::endl;
    s << "Number of particles   " << _particles  ->GetLast()+1 << std::endl;

    s << std::endl
      << "------------------------------------" << std::endl
      << " List of sensor hits:"                << std::endl
      << "------------------------------------" << std::endl
      << std::endl;

    for ( int it=0; it<=_sensor_hits->GetLast(); ++it)
    {
      SensorHit* hit = (SensorHit*) _sensor_hits->At(it);
      s << *hit << std::endl;
    }

    s << std::endl
      << "------------------------------------" << std::endl
      << " List of true hits:"                  << std::endl
      << "------------------------------------" << std::endl
      << std::endl;

    for ( int it=0; it<=_tracks->GetLast(); ++it)
    {
      Track* track = (Track*)_tracks->At(it);
      s << std::endl
        << "Detector: " << track->GetDetectorName() << std::endl
        << std::endl
        << *track <<std::endl;
    }

    s << std::endl
      << "------------------------------------" << std::endl
      << " List of particles:"                  << std::endl
      << "------------------------------------" << std::endl
      << std::endl;

    for ( int it=0; it<=_particles->GetLast(); ++it)
    {
      Particle* particle = (Particle*) _particles->At(it);
      s << *particle << std::endl;
    }

  }

} // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::Event& evt) {
  evt.Info(s);
  return s;
}
