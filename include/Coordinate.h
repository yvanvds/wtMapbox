#pragma once

#include <vector>
#include <string>

namespace MapBox {

  /* Copy of Wt::GoogleMaps::Coordinate, but it would confusing to use that namespace
  here.
  */
  class Coordinate {
  public:
    /*! \brief Default constructor
    */
    Coordinate();
    /*! \brief Creates with given latitude and longitude.
    */
    Coordinate(double latitude, double longitude);

#ifndef WT_TARGET_JAVA
    explicit Coordinate(const std::pair<double, double>& lat_long);
#endif

    /*! \brief Sets the latitude.
    */
    void setLatitude(double latitude);

    /*! \brief Sets the longitude.
    */
    void setLongitude(double longitude);

    /*! \brief Returns the latitude.
    */
    double latitude() const { return lat_; }

    /*! \brief Returns the longitude.
    */
    double longitude() const { return lon_; }

    /*! \brief Calculates the distance between two points in km (approximate).
    *
    * The calculation uses a sphere. Results can be out by 0.3%.
    */
    double distanceTo(const Coordinate &rhs) const;

    static void write(std::stringstream& os, const Coordinate &c);

#ifndef WT_TARGET_JAVA
    /*! \brief Conversion operator to pair of double.
    */
    std::pair<double, double> operator ()() const;
#endif

  private:
    double lat_, lon_;
  };

  struct Bounds {
    Coordinate min, max;
  };

#ifndef WT_TARGET_JAVA
  extern std::istream& operator>> (std::istream& i, Coordinate& coordinate);
#endif

}