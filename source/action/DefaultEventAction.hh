// ----------------------------------------------------------------------------
///  \file   DefaultEventAction.hh
///  \brief  A general-purpose user event action.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_DEA__
#define __nuCD_DEA__

#include <G4UserEventAction.hh>
#include <globals.hh>

class G4Event;
class G4GenericMessenger;

namespace nuCD
{
  class DefaultEventAction: public G4UserEventAction
  {
  public:
     DefaultEventAction();
    ~DefaultEventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

  private:
    G4GenericMessenger* _msg;
    G4int _nevt;
    G4int _nupdate; // for printing purposes
    G4double _energy_threshold; // energy threshold for storing purposes
  }; // class DefaultEventAction
  
} // namespace nuCD

#endif //__nuCD_DEA__
