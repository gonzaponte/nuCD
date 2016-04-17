// ----------------------------------------------------------------------------
///  \file   BatchSession.hh
///  \brief  
/// 
///  \author   Gonzalo Martínez Lema
///  \date     May 23rd 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_BATCH_SESSION__
#define __nuCD_BATCH_SESSION__

#include <G4UIsession.hh>
#include <fstream>


namespace nuCD {

  class BatchSession: public G4UIsession
  {
  public:
    /// Constructor
    BatchSession(G4String filename, G4UIsession* previous_session=0);
    /// Destructor
    ~BatchSession();

    virtual G4UIsession* SessionStart();
    virtual void PauseSessionStart(const G4String& Prompt);

    G4UIsession* GetPreviousSession() const;

  private:
    G4String ReadCommand();
    G4int ExecCommand(const G4String& command);

  private:
    G4bool _opened;
    std::ifstream _macrostream;
    G4UIsession* _prev; ///< Pointer to the previous session
  }; // class BatchSession

  inline G4UIsession* BatchSession::GetPreviousSession() const { return _prev; }

} // end namespace nuCD

#endif // __nuCD_BATCH_SESSION__