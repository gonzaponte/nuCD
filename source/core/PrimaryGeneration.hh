///////////////////////////////////////////////////////////////////////////////
////
////  Event generation.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuCD_PG__
#define __nuCD_PG__

#include <G4VUserPrimaryGeneratorAction.hh>

class G4VPrimaryGenerator;

namespace nuCD
{
  class PrimaryGeneration: public G4VUserPrimaryGeneratorAction
  {
  public:
    // Constructor
     PrimaryGeneration();
    // Destructor
    ~PrimaryGeneration(){  }

    void GeneratePrimaries(G4Event*);
    void SetGenerator(G4VPrimaryGenerator*);
    const G4VPrimaryGenerator* GetGenerator() const;

  private:
    G4VPrimaryGenerator* _generator; // Pointer to the primary generator
  }; // class PrimaryGeneration

  inline void  PrimaryGeneration::SetGenerator(G4VPrimaryGenerator* PG) { _generator = PG; }
  inline const G4VPrimaryGenerator* PrimaryGeneration::GetGenerator() const { return _generator; }

} // namespace nuCD

#endif // __nuCD_PG__
