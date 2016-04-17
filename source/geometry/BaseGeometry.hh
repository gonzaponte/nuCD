// ----------------------------------------------------------------------------
///  \file   BaseGeometry.h
///  \brief  Abstract base class for encapsulation of geometries.
///
///  \author   Gonzalo Martínez Lema
///  \date     May 24th 2015
///  \version  0
///
// ----------------------------------------------------------------------------

#ifndef __nuCD_BG__
#define __nuCD_BG__

#include <G4ThreeVector.hh>
#include <CLHEP/Units/SystemOfUnits.h>

using namespace CLHEP;


class G4LogicalVolume;

namespace nuCD
{
  class BaseGeometry
  {
  public:
    /// The volumes (solid, logical and physical) must be defined
    /// in this method, which will be invoked during the detector
    /// construction phase
    virtual void Construct() = 0;
    virtual G4ThreeVector GenerateVertex(const G4String&) const;

    G4LogicalVolume* GetLogicalVolume();
    G4double GetSize() const;

    /// Destructor
    virtual ~BaseGeometry();

  protected:
    /// Default constructor defined as protected so no instance of
    /// this base class can be created.
    BaseGeometry();

    void SetLogicalVolume(G4LogicalVolume*);
    void SetSize(G4double);

  private:
    /// Copy-constructor (hidden)
    BaseGeometry(const BaseGeometry&);

    /// Assignment operator (hidden)
    const BaseGeometry& operator=(const BaseGeometry&);

    G4LogicalVolume* _logic;
    G4double _size; ///< Maximum dimension of the geometry
  };


  inline BaseGeometry::BaseGeometry(): _logic(0), _size(100.*m) {}
  inline BaseGeometry::~BaseGeometry() {}
  inline G4LogicalVolume* BaseGeometry::GetLogicalVolume() { return _logic; }
  inline void BaseGeometry::SetLogicalVolume(G4LogicalVolume* lv) { _logic = lv; }
  inline G4ThreeVector BaseGeometry::GenerateVertex(const G4String&) const { return G4ThreeVector(); }
  inline void BaseGeometry::SetSize(G4double s) { _size = s; }
  inline G4double BaseGeometry::GetSize() const { return _size; }

} // end namespace nuCD

#endif //__nuCD_BG__
