// ----------------------------------------------------------------------------
///  \file   ActionsManager.hh
///  \brief
///
///  \author   Gonzalo Martinez Lema
///  \date     May 17th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_AM__
#define __nuCD_AM__

#include <G4String.hh>

class G4UserRunAction;
class G4UserEventAction;
class G4UserTrackingAction;
class G4UserSteppingAction;
class G4UserStackingAction;
class G4GenericMessenger;


namespace nuCD {

  class ActionsManager
  {
  public:
     ActionsManager();
    ~ActionsManager();

    G4UserRunAction*      CreateRunAction() const;
    G4UserEventAction*    CreateEventAction() const;
    G4UserTrackingAction* CreateTrackingAction() const;
    G4UserSteppingAction* CreateSteppingAction() const;
    G4UserStackingAction* CreateStackingAction() const;

  private:
    G4GenericMessenger* _msg;

    G4String _RA_name;  ///< Name of the user run action
    G4String _EA_name;  ///< Name of the user event action
    G4String _TA_name;  ///< Name of the user tracking action
    G4String _SPA_name; ///< Name of the user stepping action
    G4String _STA_name; ///< Name of the user stacking action
  }; // end class ActionsManager

} // end namespace nuCD

#endif // __nuCD_AM__
