///////////////////////////////////////////////////////////////////////////////
////
////  Manager to assist on writing object to file.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     08/08/2015
////  @Mofidied 08/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_WRITER__
#define __nuEI_WRITER__

#include <TFile.h>
#include <TTree.h>
#include "Event.hh"

namespace nuEI {class ParameterInfo;}

namespace nuEI
{

  class Writer
  {

  public:
    /// Constructor
    Writer();
    /// Destructor
    ~Writer() {}

  private:
    TFile* _file;   // ROOT file where the output is stored
    TTree* _tree;   // ROOT tree where the events are stored
    Event* _event;  // Pointer to the event to be stored
    bool   _isopen; // Safety flag

  public:
    bool Open(const std::string filename, std::string option);
    void Write(Event& event);
    void Close();
    bool IsOpen() const;
    void WriteMetadata(ParameterInfo* mdata);

  }; // class Writer

  inline bool Writer::IsOpen() const {return _isopen;}

} // end namespace nuEI

#endif // __nuEI_WRITER__
