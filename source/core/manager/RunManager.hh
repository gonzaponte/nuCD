///////////////////////////////////////////////////////////////////////////////
////
////  Class to organize run orders.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuCD_RM__
#define __nuCD_RM__

#include <G4RunManager.hh>

class G4GenericMessenger;

namespace nuCD
{

  class RunManager: public G4RunManager
  {
  public:
     RunManager(G4String init_macro);
    ~RunManager();

    virtual void Initialize();

    G4int GetNevents() const;

  private:
    void RegisterMacro(const G4String&);
    void RegisterDelayedMacro(const G4String&);
    void ExecuteMacroFile(const char*);

    // Set seed for random number generator. If seed is negative or zero,
    // the system time is used.
    void SetRNGseed(G4int);

  private:
    G4GenericMessenger*   _msg;         // Messenger
    std::vector<G4String> _macros;      // Macros to be read (file names)
    std::vector<G4String> _delayed;     // Delayed macros (see botom of the file)
    G4String              _historyFile; // File where history is written

  }; // class RunManager

  inline void RunManager::RegisterMacro(const G4String& macro) { _macros.push_back(macro);}
  inline void RunManager::RegisterDelayedMacro(const G4String& macro) {_delayed.push_back(macro);}

} // namespace nuCD

#endif // __nuCD_RM__


/*
Some commands only work if executed after the initialization of
this class. Those are the orders called delayed.
*/
