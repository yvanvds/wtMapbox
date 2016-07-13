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
    case ST_VECTOR: return "vector";
    case ST_RASTER: return "raster";
    case ST_GEOJSON: return "geojson";
    case ST_IMAGE: return "image";
    case ST_VIDEO: return "video";
    }
  }

  Source::Source(SOURCETYPE type) : type_(type), id_(getNextSourceID())
  {

  }

 


} // namespace MapBox