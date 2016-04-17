// ----------------------------------------------------------------------------
///  \file   DefaultTrackingAction.hh
///  \brief  General-purpose user tracking action.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_DTA__
#define __nuCD_DTA__

#include <G4UserTrackingAction.hh>

class G4Track;

namespace nuCD
{
  class DefaultTrackingAction: public G4UserTrackingAction
  {
  public:
             DefaultTrackingAction();
    virtual ~DefaultTrackingAction();

    // virtual void PreUserTrackingAction(const G4Track*);
    // virtual void PostUserTrackingAction(const G4Track*);
  }; // class DefaultTrackingAction

} // namespace nuCD

#endif //__nuCD_DTA__
