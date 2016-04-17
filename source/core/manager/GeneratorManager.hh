// ----------------------------------------------------------------------------
///  \file   GeneratorManager.hh
///  \brief  Manager class for the construction of primary generators.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 23rd 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_GENM__
#define __nuCD_GENM__

#include <G4String.hh>

class G4VPrimaryGenerator;
class G4GenericMessenger;


namespace nuCD {

  /// Manager class for the construction of primary generators
  /// chosen by the user via messenger.

  class GeneratorManager
  {
  public:
    /// Constructor. Defines the messenger commands.
    GeneratorManager();
    /// Destructor
    ~GeneratorManager();
    /// Returns an instance of the chosen generator
    G4VPrimaryGenerator* CreateGenerator() const;

  private:
    G4GenericMessenger* _msg; ///< Pointer to the messenger
    G4String _name; ///< Name of the chosen primary generator
  }; // class GeneratorManager

} // end namespace nuCD

#endif // __nuCD_GENM__
