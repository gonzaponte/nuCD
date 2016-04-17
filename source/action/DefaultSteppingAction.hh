// ----------------------------------------------------------------------------
///  \file   DefaultSteppingAction.hh
///  \brief  General-purpose user stepping action.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_DSTEA__
#define __nuCD_DSTEA__

#include <G4UserSteppingAction.hh>

class G4Step;


namespace nuCD
{
  class DefaultSteppingAction: public G4UserSteppingAction
  {
  public:
     DefaultSteppingAction();
    ~DefaultSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
  };// class DefaultSteppingAction

inline void DefaultSteppingAction::UserSteppingAction(const G4Step* ){ return; }
    
} // namespace nuCD

#endif //__nuCD_DSTEA__
