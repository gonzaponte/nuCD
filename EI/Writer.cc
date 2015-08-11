///////////////////////////////////////////////////////////////////////////////
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#include "Writer.hh"

//#include <sys/stat.h>
//#include <sstream>

namespace nuEI
{

  Writer::Writer() : _file(0), _tree(0), _event(0), _isopen(false)
  {}

  void Writer::Open(const std::string filename, std::string option)
  {
    if (_file) delete _file;
/*
    // Check if the path exists
    std::istringstream iss(filename);
    std::vector<std::string> myline;
    std::string text;
    while (getline(iss, text, '/')) {
      myline.push_back(text);
    }

    std::string path;
    if (myline.size() == 1) {
      path = ".";
    }
    for (int i=0; i<myline.size()-1; ++i) {
      path.append(myline[i]);
      if (i != myline.size()-2)
	path.append("/");
    }

    struct stat st;
    if (stat(path.c_str(),&st) != 0)
      return false;
*/
    _event = 0;
    _file  = new TFile(filename.c_str(), option.c_str());
    _tree  = new TTree("EventTree","nuEI event tree");
    _tree->Branch("EventBranch","nuEI::Event",&_event);
    _isopen = true;
}

  void Writer::Close()
  {
    if (!_file || !_file->IsOpen())
      return;

    _file->Write();
    _file->Close();

    _isopen = false;
  }

  void Writer::Write(Event& event)
  {
    _event = &event;

    if (!_tree)
    std::cerr << "======================================= "
              << "Error in nuEI::Writer::Write(Event&):   "
              << "The event tree does not exist.          "
              << "======================================= " << std::endl;

    _tree->Fill();
  }

}
