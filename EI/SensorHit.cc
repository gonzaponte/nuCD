///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "SensorHit.hh"

ClassImp(nuEI::SensorHit)

namespace nuEI
{
  SensorHit::SensorHit() :
  _detector_type("Unknowm"), _id(-1), _bin_width(0),
  _total_counts(0), _waveform(), _position()
  {  }

  SensorHit::SensorHit(std::string sensortype) :
  _detector_type(sensortype), _id(-1), _bin_width(0),
  _total_counts(0), _waveform(), _position()
  {  }

  void SensorHit::SetSample(double amp, double time)
  {
    std::pair<double, int> sample( time, amp);
    _waveform.push_back(sample);
  }

  void SensorHit::Info(std::ostream& s) const
  {
    s << "Detector type: " << _detector_type << std::endl
      << "ID:            " << _id            << std::endl
      << "Total charge:  " << _total_counts  << std::endl;
  }

} // namespace nuEI

std::ostream& operator << (std::ostream& s, const nuEI::SensorHit& sh) {
  sh.Info(s);
  return s;
}
