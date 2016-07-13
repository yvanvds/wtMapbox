#include "Coordinate.h"
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// for visual studio sprintf
#pragma warning(disable:4996)


namespace MapBox {

  Coordinate::Coordinate()
    : lat_(0), lon_(0)
  { }

  Coordinate::Coordinate(double lat, double lon)
  {
    setLatitude(lat);
    setLongitude(lon);
  }

#ifndef WT_TARGET_JAVA
  Coordinate::Coordinate(const std::pair<double, double>& lat_long)
  {
    setLatitude(lat_long.first);
    setLongitude(lat_long.second);
  }
#endif 

  void Coordinate::setLatitude(double latitude)
  {
    if (latitude < -90.0 || latitude > 90.0)
      throw std::out_of_range("invalid latitude: "
      + boost::lexical_cast<std::string>(latitude));

    lat_ = latitude;
  }

  void Coordinate::setLongitude(double longitude)
  {
    if (longitude < -180.0 || longitude > 180.0)
      throw std::out_of_range("invalid longitude: "
      + boost::lexical_cast<std::string>(longitude));

    lon_ = longitude;
  }

  double Coordinate::distanceTo(const Coordinate &rhs) const
  {
    const double lat1 = lat_ * M_PI / 180.0;
    const double lat2 = rhs.latitude() * M_PI / 180.0;
    const double deltaLong = (rhs.longitude() - lon_) * M_PI / 180.0;
    const double angle = std::sin(lat1) * std::sin(lat2)
      + std::cos(lat1) * std::cos(lat2) * std::cos(deltaLong);
    const double earthRadius = 6371.0; // km
    const double dist = earthRadius * std::acos(angle);

    return dist;
  }

#ifndef WT_TARGET_JAVA
  std::pair<double, double> Coordinate::operator ()() const
  {
    return std::make_pair(lat_, lon_);
  }

  std::istream& operator>> (std::istream& i, Coordinate& c)
  {
    double lat, lon;
    i >> lat >> std::ws >> lon;
    c.setLatitude(lat);
    c.setLongitude(lon);

    return i;
  }
#endif

  // included in Wt, web/WebUtils, but that's not reachable here
  static inline char *generic_double_to_str(double d, char *buf)
  {
    if (!boost::math::isnan(d)) {
      if (!boost::math::isinf(d)) {
        sprintf(buf, "%.7g", d);
      }
      else {
        if (d > 0) {
          sprintf(buf, "Infinity");
        }
        else {
          sprintf(buf, "-Infinity");
        }
      }
    }
    else {
      sprintf(buf, "NaN");
    }
    return buf;
  }

  // included in Wt, web/WebUtils, but that's not reachable here
  char *round_js_str(double d, int digits, char *buf) {
    return generic_double_to_str(d, buf);
  }

  // altered because syntax is different from google maps
  void Coordinate::write(std::stringstream& os, const Coordinate &c)
  {
    char b1[35];
    char b2[35];
    os << "["
      << round_js_str(c.longitude(), 15, b1)
      << "," << round_js_str(c.latitude(), 15, b2) << "]";
  }

}
