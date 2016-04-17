// ----------------------------------------------------------------------------
///  \file   DefaultStackingAction.hh
///  \brief  General-purpose user stacking action.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_DSTAA__
#define __nuCD_DSTAA__

#include <G4UserStackingAction.hh>


namespace nuCD
{
  class DefaultStackingAction: public G4UserStackingAction
  {
  public:
     DefaultStackingAction();
    ~DefaultStackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    virtual void NewStage();
    virtual void PrepareNewEvent();
  };// class DefaultStackingAction
    
inline G4ClassificationOfNewTrack DefaultStackingAction::ClassifyNewTrack(const G4Track*) { return fUrgent; }
inline void DefaultStackingAction::NewStage() { return; }
inline void DefaultStackingAction::PrepareNewEvent(){ return; }
    
} // end namespace nuCD

#endif // __nuCD_DSTAA__
