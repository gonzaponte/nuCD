// ----------------------------------------------------------------------------
///  \file   GeometryManager.hh
///  \brief  Manager class to create geometries chosen by the user
///
///  \author   Gonzalo Martínez Lema
///  \date     May 23rd 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_GEOM__
#define __nuCD_GEOM__

#include <G4String.hh>

class G4GenericMessenger;


namespace nuCD {

  class BaseGeometry;

  /// Manager class to handle the creation of geometries according
  /// to the user's input via messenger commands.

  class GeometryManager
  {
  public:
    GeometryManager();
    ~GeometryManager();

    BaseGeometry* CreateGeometry() const;

  private:
    G4GenericMessenger* _msg;
    G4String _name;
  }; // class GeometryManager

} // namespace nuCD

#endif // __nuCD_GEOM__
