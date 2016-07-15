#include "Source.h"
#include "Coordinate.h"

#include <sstream>

namespace MapBox {

  int nextSourceID = 0;

  Wt::WString getNextSourceID() {
    std::stringstream stream;
    stream << "mapsource-" << nextSourceID++;
    return stream.str();
  }

  Wt::WString typeAsString(SOURCETYPE type) {
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

  Source & Source::setFromURL(const Wt::WString & url) {
    url_ = url;
    return *this;
  }


} // namespace MapBox