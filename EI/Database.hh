///////////////////////////////////////////////////////////////////////////////
////
////  Database contaning the particles' information.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     09/08/2015
////  @Mofidied 09/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_DATABASE__
#define __nuEI_DATABASE__

#include <string>
#include <map>

#include <TObject.h>

namespace nuEI
{
  class Database : public TObject
  {

  public:
    // Empty constructor
     Database();
    // Destructor
    ~Database();

  private:
    std::map< std::string, int > _codes;     // key: name value: code
    std::map< int, std::string > _names;     // key: code value: name
    std::map< int, double >      _masses;    // key: code value: mass
    std::map< int, int >         _charges;   // key: code value: charge
    std::map< int, double >      _lifetimes; // key: code value: lifetime

    void LoadDatabase( std::string& );

  public:
    int GetPDGcode( std::string& name ) const;
    std::string GetName( int code ) const ;

    double GetMass( int code ) const;
    double GetMass( std::string& name ) const;

    double GetCharge( int code ) const;
    double GetCharge( std::string& name ) const;

    double GetLifetime( int code ) const;
    double GetLifetime( std::string& name ) const;

    ClassDef(Database,1);

  }; // class Database

  // INLINE functions
  inline int GetPDGcode( std::string& name ) const{ return _codes[name];}
  inline std::string GetName( int code ) const{ return _names[code];}

  inline double GetMass( int code ) const{ return _masses[code];}
  inline double GetMass( std::string& name ) const{ return GetMass(_codes[name]);}

  inline double GetCharge( int code ) const{ return _charges[code];}
  inline double GetCharge( std::string& name ) const{ return GetCharge(_codes[name]);}

  inline double GetLifetime( int code ) const{ return _lifetimes[code];}
  inline double GetLifetime( std::string& name ) const{ return GetLifetime(_codes[name]);}

} // namespace nuEI

#endif // __nuEI_DATABASE__
