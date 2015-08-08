///////////////////////////////////////////////////////////////////////////////
////
////  Class with the description of a particle.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     07/08/2015
////  @Mofidied 07/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_PARTICLE__
#define __nuEI_PARTICLE__

#include <string>
#include <map>

#include <TObject.h>
#include <TLorentzVector.h>
#include <TRef.h>
#include <TRefArray.h>
#include <TDatabasePDG.h>

namespace nuEI { class Track; }

namespace nuEI
{
  class Particle : public TObject
  {

  public:
    // Empty constructor
    Particle();
    // Named constructor
    Particle(std::string name);
    // Code constructor
    Particle(int pdg);
    /// Destructor
    ~Particle();

  private:
    int _particleID;                  // Geant4 ID
    int _PDGcode;                     // PDG code of the particle
    std::string _name;                // name of the particle

    double _mass;                     // mass. It's set through the PDG
    double _charge;                   // charge. It's set through the PDG
    double _lifetime;                 // life time. It's set through the PDG
    double _track_length;             // length of the associated track
    bool   _primary;                  // true if the particle is primary (shot by Geant)

    TLorentzVector _initial_vertex;   // point and time of generation
    TLorentzVector _decay_vertex;     // point and time of death
    TLorentzVector _initial_momentum; // initial momentum and energy
    TLorentzVector _decay_momentum;   // final momentum and energy

    std::string _initial_volume;       // name of the volume where the particle was created
    std::string _decay_volume;        // name of the volume where the particle decays
    std::string _creator_process;     // name of the process by which the particle was created

    TRef      _mother;                // reference to the mother particle
    TRefArray _tracks;                // reference to the true hits made by the particle
    TRefArray _daughters;             // array of references to the secondary particles comming from this one

    TDatabasePDG _PDG_manager;        // Interface with PDG database

    AddProperties();                  // Set properties from PDG database
  public:
    void SetParticleID(int ID);
    int  GetParticleID() const;
    void SetPDGcode(int code);
    int  GetPDGcode() const;
    void SetName(const std::string& name);
    void SetName(int code);
    const std::string& GetName() const;

    double GetMass() const;
    double GetCharge() const;
    double InitialEnergy() const;
    double InitialMomentum() const;
    double DecayEnergy() const;
    double DecayMomentum() const;
    void   SetTrackLength(double L);
    double GetTrackLength() const;
    void   SetPrimary(bool primary);
    bool   IsPrimary() const;

    void SetInitialVertex(double x, double y, double z, double t);
    void SetInitialVertex(TLorentzVector V);
    TLorentzVector GetInitialVertex() const;
    void GetInitialVertex(double xyzt[]) const;

    void SetDecayVertex(double x, double y, double z, double t);
    void SetDecayVertex(TLorentzVector V);
    TLorentzVector GetDecayVertex() const;
    void GetDecayVertex(double xyzt[]) const;

    void SetInitialMomentum(double x, double y, double z, double E);
    void SetInitialMomentum(TLorentzVector V);
    TLorentzVector GetInitialMomentum() const;
    void GetInitialMomentum( double xyze[]) const;

    void SetDecayMomentum(double x, double y, double z, double E);
    void SetDecayMomentum(TLorentzVector V);
    TLorentzVector GetDecayMomentum() const;
    void GetDecayMomentum( double xyze[] ) const;

    void SetInitialVolume(const std::string& volume);
    const std::string& GetInitialVolume() const;
    void SetDecayVolume(const std::string& volume);
    const std::string& GetDecayVolume() const;
    void SetCreatorProcess(const std::string& process);
    const std::string& GetCreatorProcess() const;

    void SetMother(Particle* mother);
    const Particle* GetMother() const;
    void AddTrack(Track* track);
    const TRefArray GetTracks() const;
    Track* GetTrack(const std::string& det);
    void AddDaughter(Particle* daughter);
    const TRefArray GetDaughters() const;

    void Info(ostream& s) const;

    ClassDef(Particle,4);

  }; // class Particle

  // INLINE functions
  inline void Particle::SetParticleID(int ID) {_particleID = ID;}
  inline int  Particle::GetParticleID() const {return _particleID;}
  inline void Particle::SetPDGcode(int code) {_PDGcode = code;AddProperties()}
  inline int  Particle::GetPDGcode() const {return _PDGcode;}
  inline void Particle::SetName( const std::string& name ) {_name = name;}
  inline const std::string& Particle::GetName() const {return _name;}

  inline double Particle::GetMass()         const {return _mass;}
  inline double Particle::GetCharge()       const {return _charge;}
  inline double Particle::InitialEnergy()   const {return _initial_momentum.Energy();}
  inline double Particle::InitialMomentum() const {return _initial_momentum.P();}
  inline double Particle::DecayEnergy()     const {return _decay_momentum.Energy();}
  inline double Particle::DecayMomentum()   const {return _decay_momentum.P();}
  inline void   Particle::SetTrackLength(double L){ _track_length = L;}
  inline double Particle::GetTrackLength()  const {return _track_length;}
  inline void   Particle::SetPrimary(bool primary){_primary = primary;}
  inline bool   Particle::IsPrimary()        const{return _primary;}

  inline void Particle::SetInitialVertex(double x, double y, double z, double t){ _initial_vertex.SetXYZT(x,y,z,t);}
  inline void Particle::SetInitialVertex(TLorentzVector V){ _initial_vertex = V;}
  inline TLorentzVector Particle::GetInitialVertex() const{ return _initial_vertex;}
  inline void Particle::GetInitialVertex(double xyzt[]) const{ _initial_vertex.GetXYZT( xyzt ); return;}

  inline void Particle::SetDecayVertex(double x, double y, double z, double t){ _decay_vertex.SetXYZT(x,y,z,t);}
  inline void Particle::SetDecayVertex(TLorentzVector V){ _decay_vertex = V;}
  inline TLorentzVector Particle::GetDecayVertex() const{ return _decay_vertex;}
  inline void Particle::GetDecayVertex(double xyzt[]) const{ _decay_vertex.GetXYZT( xyzt ); return;}

  inline void Particle::SetInitialMomentum(double x, double y, double z, double E){ _initial_momentum.SetXYZT(x,y,z,E);}
  inline void Particle::SetInitialMomentum(TLorentzVector V){ _initial_momentum = V;}
  inline TLorentzVector Particle::GetInitialMomentum() const{ return _initial_momentum;}
  inline void Particle::GetInitialMomentum( double xyze[]) const{ _initial_momentum.GetXYZT( xyze ); return;}

  inline void Particle::SetDecayMomentum(double x, double y, double z, double E){ _decay_momentum.SetXYZT(x,y,z,E);}
  inline void Particle::SetDecayMomentum(TLorentzVector V){ _decay_momentum = V;}
  inline TLorentzVector Particle::GetDecayMomentum() const{ return _decay_momentum;}
  inline void Particle::GetDecayMomentum( double xyze[] ) const{ _decay_momentum.GetXYZT( xyze ); return;}

  inline void  Particle::SetInitialVolume(const std::string& volume){ _initial_volume = volume;}
  inline const std::string& Particle::GetInitialVolume() const{ return _initial_volume;}
  inline void  Particle::SetDecayVolume(const std::string& volume){ _decay_volume = volume;}
  inline const std::string& Particle::GetDecayVolume() const{ return _decay_volume;}
  inline void  Particle::SetCreatorProcess(const std::string& process){ _creator_process = process;}
  inline const std::string& Particle::GetCreatorProcess() const{ return _creator_process;}

  inline void Particle::SetMother(const Particle* mother ){ _mother = mother; }
  //inline const Particle* Particle::GetMother(const Particle* mother ){ return _mother; }
  inline void Particle::AddTrack(const Track* track ){ _tracks->AddLast(track); }
  inline const TRefArray& Particle::GetTracks(){ return _tracks; }
  inline void Particle::AddDaughter(const Particle* particle ){ _particles->AddLast(particle); }
  inline const TRefArray& Particle::GetDaughters(){ return _particles; }

} // namespace nuEI

ostream& operator << (ostream& s, const nuEI::Particle& p);

#endif // __nuEI_PARTICLE__
