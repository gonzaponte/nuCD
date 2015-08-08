///////////////////////////////////////////////////////////////////////////////
////
////  Class containing the description of a hit in a sensor of the detector.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     08/08/2015
////  @Mofidied 08/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_SENSORHIT__
#define __nuEI_SENSORHIT__

#include <iostream>
#include <TObject.h>
#include <TVector3.h>

namespace nuEI
{

  class SensorHit : public TObject
  {

  public:
    // empty constructor
    SensorHit();
    // naming constructor
    SensorHit(std::string sensortype);
    // destructor
    ~SensorHit();

  private:
    std::string _detector_type;                     // type of sensor
    int _id;                                        // unique identification number
    double _bin_width;                              // width of the time bins
    double _total_counts;                           // total counts summed over all the times
    std::vector<std::pair<double, int> > _waveform; // times and counts of the sensor's response
    TVector3 _position;                             // 3D position of the sensor

  public:

    void SetSample(double amp, double time);
    const std::vector<std::pair<double,int> >& GetWaveform() const;

    void   SetAmplitude(double amplitude);
    double GetAmplitude() const;

    void SetID(int id);
    int  GetID() const;

    void   SetBinWidth(double width);
    double GetBinWidth() const;

    void     SetPosition(double x, double y, double z);
    TVector3 GetPosition() const;

    void               SetDetectorName(std::string);
    const std::string& GetDetectorName() const;

    void Info(ostream& s) const;

    ClassDef(SensorHit,1);

  };

  // IN-LINE FUNCTIONS

  inline const std::vector<std::pair<double, int> >& SensorHit::GetWaveform() const {return _waveform;}
  inline void     SensorHit::SetAmplitude(double amplitude) {_amplitude = amplitude;}
  inline double   SensorHit::GetAmplitude() const {return _amplitude;}
  inline void     SensorHit::SetID(int id) {_id = id;}
  inline int      SensorHit::GetID() const {return _id;}
  inline void     SensorHit::SetBinWidth(double width) {_bin_width = width;}
  inline double   SensorHit::GetBinWidth() const {return _bin_width;}
  inline void     SensorHit::SetPosition(double x, double y, double z) {_position.SetXYZ(x,y,z);}
  inline TVector3 SensorHit::GetPosition() const {return _position;}
  inline void               SensorHit::SetDetectorType(std::string type) {_detector_type = type;}
  inline const std::string& SensorHit::GetDetectorType() const {return _detector_type;}

} // end namespace nuEI

ostream& operator << (ostream& s, const nuEI::SensorHit& lh);

#endif // __nuEI_SENSORHIT__
