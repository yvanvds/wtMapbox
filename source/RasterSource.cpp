#include "RasterSource.h"
#include "Enumerations.h"
#include "Map.h"

namespace MapBox {

  Wt::WString RasterSource::render(Map * parent)
  {
    parent_ = parent;

    std::stringstream stream;
    stream
      << "'" << id_ << "', { \n"
      << "  type: 'raster', \n"
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
