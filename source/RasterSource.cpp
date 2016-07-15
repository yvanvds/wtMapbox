#include "RasterSource.h"
#include "Enumerations.h"


namespace MapBox {

  std::string RasterSource::render()
  {
    std::stringstream stream;
    stream
      << "'" << id_ << "', { \n"
      << "  type: 'vector', \n"
      << "  url: '" << url_ << "', \n"
      << "  tileSize: " << tileSize_ << " \n"
      << "} \n";
    return stream.str();
  }

  RasterSource::RasterSource()
    : Source(SOURCETYPE::Raster)
  {
  }

  RasterSource & RasterSource::tileSize(int value)
  {
    tileSize_ = value;
    return *this;
  }

}