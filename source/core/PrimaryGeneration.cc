///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "core/PrimaryGeneration.hh"

#include <G4VPrimaryGenerator.hh>
#include <G4Event.hh>

namespace nuCD
{
  PrimaryGeneration::PrimaryGeneration() :
  G4VUserPrimaryGeneratorAction(), _generator(0) {  }

  void PrimaryGeneration::GeneratePrimaries(G4Event* event)
  {
    if (!_generator) G4Exception("", "", FatalException, "");
    _generator->GeneratePrimaryVertex(event);
  }

}
