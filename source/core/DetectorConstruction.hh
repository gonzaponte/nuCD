///////////////////////////////////////////////////////////////////////////////
////
////  Detector setup (no actual detector description here)
////
////  @Author   Gonzalo Martínez Lema
////  @Date     12/08/2015
////  @Mofidied 12/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuCD_DC__
#define __nuCD_DC__

#include <G4VUserDetectorConstruction.hh>

class G4GenericMessenger;

namespace nuCD
{
  class BaseGeometry;

  class DetectorConstruction: public G4VUserDetectorConstruction
  {
  public:
    // Constructor
     DetectorConstruction();
    // Destructor
    ~DetectorConstruction();

    // Mandatory (called by the run manager).
    virtual G4VPhysicalVolume* Construct();

    void SetGeometry(BaseGeometry*);
    const BaseGeometry* GetGeometry() const;

  private:
    BaseGeometry* _geometry;
  }; // class DetectorConstruction

  inline void DetectorConstruction::SetGeometry(BaseGeometry* g) { _geometry = g; }
  inline const BaseGeometry* DetectorConstruction::GetGeometry() const { return _geometry; }

} // namespace nuCD

#endif // __nuCD_DC__
