// ----------------------------------------------------------------------------
///  \file   nuBeam.hh
///  \brief  Primary generator for neutrino events.
///  
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_nuBEAM__
#define __nuCD_nuBEAM__

#include <G4VPrimaryGenerator.hh>

class G4GenericMessenger;
class G4Event;
class G4ParticleDefinition;

namespace nuCD
{

  class BaseGeometry;

  /// Primary generator (concrete class of G4VPrimaryGenerator) for events 
  /// consisting of a neutrino beam. The user must specify via configuration
  /// parameters the neutrino family. Its energy is generated with flat
  /// random probability between Emin and Emax.
  /// Note: for fixed energy Emin = Emax = E
  
  class nuBeam: public G4VPrimaryGenerator
  {
  public:
     nuBeam();
    ~nuBeam();
    
    void GeneratePrimaryVertex(G4Event*);

  private:

    void SetParticleDefinition(G4String);
    G4double RandomEnergy() const;
    
    G4GenericMessenger*   _msg;
    G4ParticleDefinition* _particle_definition;
    const BaseGeometry*   _geometry;
      
    G4double _Emin;
    G4double _Emax;
    G4double _theta;
    G4double _phi;
    G4double _x0;
    G4double _y0;
    G4double _z0;
   
  }; //class nuBeam

} // end namespace nuCD

#endif //__nuCD_nuBEAM__
