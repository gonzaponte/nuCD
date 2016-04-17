// ----------------------------------------------------------------------------
///  \file 
///  \brief
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_CYLINDRIC_CHAMBER__
#define __nuCD_CYLINDRIC_CHAMBER__

#include "BaseGeometry.hh"

class G4GenericMessenger;


namespace nuCD
{

  class CylindricChamber: public BaseGeometry
  {
  public:
     CylindricChamber();
    ~CylindricChamber();

    virtual G4ThreeVector GenerateVertex(const G4String& region) const;
    virtual void Construct();
      
  private:
    G4GenericMessenger* _msg; 
  }; // class CylindricChamber

} // end namespace nuCD

#endif //__nuCD_CYLINDRIC_CHAMBER__
