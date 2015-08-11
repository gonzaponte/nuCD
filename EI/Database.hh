///////////////////////////////////////////////////////////////////////////////
////
////  Database contaning the particles' information.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     10/08/2015
////  @Mofidied 10/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_DATABASE__
#define __nuEI_DATABASE__

#include <TObject.h>

#include <string>
#include <map>

namespace nuEI
{
  class Database : public TObject
  {

  public:
    static Database* GetInstance();

  private:
    // Empty constructor
     Database();
    // Destructor
    ~Database(){ }

    static Database*             _instance;  // instance of the class
    std::map< std::string, int > _codes;     // key: name value: code
    std::map< int, std::string > _names;     // key: code value: name
    std::map< int, double >      _masses;    // key: code value: mass
    std::map< int, int >         _charges;   // key: code value: charge
    std::map< int, double >      _lifetimes; // key: code value: lifetime

    void LoadDatabase();

  public:
    int GetPDGcode( std::string& name ) ;
    std::string GetName( int code )  ;

    double GetMass( int code ) ;
    double GetMass( std::string& name ) ;

    double GetCharge( int code ) ;
    double GetCharge( std::string& name ) ;

    double GetLifetime( int code ) ;
    double GetLifetime( std::string& name ) ;

    ClassDef(Database,1);

  }; // class Database

  // INLINE functions
  inline int Database::GetPDGcode( std::string& name ) { return _codes[name];}
  inline std::string Database::GetName( int code ) { return _names[code];}

  inline double Database::GetMass( int code ) { return _masses[code];}
  inline double Database::GetMass( std::string& name ) { return GetMass(_codes[name]);}

  inline double Database::GetCharge( int code ) { return _charges[code];}
  inline double Database::GetCharge( std::string& name ) { return GetCharge(_codes[name]);}

  inline double Database::GetLifetime( int code ) { return _lifetimes[code];}
  inline double Database::GetLifetime( std::string& name ) { return GetLifetime(_codes[name]);}

} // namespace nuEI

#endif // __nuEI_DATABASE__
