// ----------------------------------------------------------------------------
///  \file   DefaultRunAction.hh
///  \brief  General purpose run action. Does nothing.
/// 
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_DRA__
#define __nuCD_DRA__

#include <G4UserRunAction.hh>


namespace nuCD
{
  class DefaultRunAction: public G4UserRunAction
  {
  public:
     DefaultRunAction();
    ~DefaultRunAction();
  
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
  }; // class DefaultRunAction

} // namespace nuCD

#endif //__nuCD_DRA__

