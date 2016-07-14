#include "Source.h"
#include "Coordinate.h"

#include <sstream>

namespace MapBox {

  int nextSourceID = 0;

  std::string getNextSourceID() {
    std::stringstream stream;
    stream << "mapsource-" << nextSourceID++;
    return stream.str();
  }

  std::string typeAsString(SOURCETYPE type) {
    switch (type) {
    case SOURCETYPE::Vector : return "vector" ;
    case SOURCETYPE::Raster : return "raster" ;
    case SOURCETYPE::GeoJSON: return "geojson";
    case SOURCETYPE::Image  : return "image"  ;
    case SOURCETYPE::Video  : return "video"  ;
    }
  }

  Source::Source(SOURCETYPE type) 
    : type_(type)
    , id_(getNextSourceID())
  {

  }

  Source & Source::setFromURL(const std::string & url) {
    url_ = url;
    return *this;
  }


} // namespace MapBox