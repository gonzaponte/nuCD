///////////////////////////////////////////////////////////////////////////////
////
////  Contains a numerical definition of units.
////
////  @Author   Gonzalo Martínez Lema
////  @Date     07/08/2015
////  @Mofidied 07/08/2015
////
///////////////////////////////////////////////////////////////////////////////

#ifndef __nuEI_UNITS__
#define __nuEI_UNITS__

namespace nuEI
{
    // length, surface and volume
    static const double millimeter  = 1.0;
    static const double millimeter2 = millimeter*millimeter;
    static const double millimeter3 = millimeter*millimeter*millimeter;

    static const double centimeter  = 10*millimeter;
    static const double centimeter2 = centimeter*centimeter;
    static const double centimeter3 = centimeter*centimeter*centimeter;

    static const double decimeter  = 100*millimeter;
    static const double decimeter2 = decimeter*decimeter;
    static const double decimeter3 = decimeter*decimeter2;
    static const double liter = decimeter3;

    static const double meter  = 1000*millimeter;
    static const double meter2 = meter*meter;
    static const double meter3 = meter*meter*meter;

    static const double kilometer = 1000*meter;
    static const double kilometer2 = kilometer*kilometer;
    static const double kilometer3 = kilometer*kilometer*kilometer;

    static const double micrometer = 1.0e-6  * meter;
    static const double  nanometer = 1.0e-9  * meter;
    static const double  angstrom  = 1.0e-10 * meter;
    static const double  fermi     = 1.0e-15 * meter;

    static const double      barn = 1.0e-28*meter2;
    static const double millibarn = 1.0e-3 *barn;
    static const double microbarn = 1.0e-6 *barn;
    static const double  nanobarn = 1.0e-9 *barn;
    static const double  picobarn = 1.0e-12*barn;

    // angles
    static const double pi          = 3.14159265358979323846;
    static const double   steradian = 1.0;
    static const double      radian = 1.0;
    static const double milliradian = 1.0e-3*radian;
    static const double degree      = (pi/180.0)*radian;


    // time
    static const double nanosecond  = 1.0;
    static const double     second  = 1.0e+9 *nanosecond;
    static const double millisecond = 1.0e-3 *second;
    static const double microsecond = 1.0e-6 *second;
    static const double  picosecond = 1.0e-12*second;

    static const double minute = 60 * second;
    static const double hour   = 60 * minute;
    static const double day    = 24 * hour;
    static const double week   = 7 * day;
    static const double month  = 30 * day;
    static const double year   = 365.25 * day;

    static const double     hertz = 1.0/second;
    static const double kilohertz = 1.0e+3*hertz;
    static const double megahertz = 1.0e+6*hertz;

    // charge
    static const double eplus = 1.0;
    static const double e_SI  = 1.60217733e-19;
    static const double coulomb = eplus/e_SI;

    // energy
    static const double megaelectronvolt = 1.0 ;
    static const double     electronvolt = 1.0e-6*megaelectronvolt;
    static const double kiloelectronvolt = 1.0e-3*megaelectronvolt;
    static const double gigaelectronvolt = 1.0e+3*megaelectronvolt;
    static const double teraelectronvolt = 1.0e+6*megaelectronvolt;
    static const double petaelectronvolt = 1.0e+9*megaelectronvolt;
    static const double joule = electronvolt/e_SI;

    // mass
    static const double  kilogram = joule*second*second/(meter*meter);
    static const double      gram = 1.0e-3*kilogram;
    static const double milligram = 1.0e-3*gram;
    static const double       ton = 1.0e+3*kilogram;
    static const double   kiloton = 1.0e+3*ton;

    // pressure
    static const double pascal     = joule/meter/m2;
    static const double bar        = 1.0e5  * pascal;
    static const double atmosphere = 101325 * pascal;

    // electric potential
    static const double megavolt = megaelectronvolt/eplus;
    static const double kilovolt = 1.0e-3*megavolt;
    static const double     volt = 1.0e-6*megavolt;

    // temperature
    static const double kelvin = 1.0;

    // activity
    static const double becquerel = hertz ;
    static const double curie = 3.7e+10 * becquerel;

    // aliases: shorter and common names
    static const double mm  = millimeter;
    static const double mm2 = millimeter2;
    static const double mm3 = millimeter3;

    static const double cm  = centimeter;
    static const double cm2 = centimeter2;
    static const double cm3 = centimeter3;

    static const double m  = meter;
    static const double m2 = meter2;
    static const double m3 = meter3;

    static const double km  = kilometer;
    static const double km2 = kilometer2;
    static const double km3 = kilometer3;

    static const double l = liter;

    static const double rad  = radian;
    static const double mrad = milliradian;
    static const double sr   = steradian;
    static const double deg  = degree;

    static const double ns  = nanosecond;
    static const double  s  = second;
    static const double ms  = millisecond;
    static const double min = minute;
    static const double yr = year;

    static const double MeV = megaelectronvolt;
    static const double  eV = electronvolt;
    static const double keV = kiloelectronvolt;
    static const double GeV = gigaelectronvolt;
    static const double TeV = teraelectronvolt;
    static const double PeV = petaelectronvolt;

    static const double  kg = kilogram;
    static const double   g = gram;
    static const double  mg = milligram;

    static const double  Pa = pascal;
    static const double  atm = atmosphere;

    static const double MV = megavolt;
    static const double kV = kilovolt;
    static const double  V = volt;

    static const double Bq = becquerel;

} // namespace nuEI

#endif // __nuEI_UNITS__
