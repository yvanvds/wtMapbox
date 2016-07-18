#include "Source.h"
#include "Coordinate.h"
#include "Conversions.h"
#include "Map.h"

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
    , parent_(nullptr)
  {

  }

  Source & Source::set(const Wt::WString & url) {
    url_ = url;

    if (parent_ != nullptr) {
      // map is already rendered. Change url on client.
      std::stringstream stream;
      stream << "try {"
        << parent_->jsRef() << ".map.getSource(" << Quote(id()) << ")"
        << ".setData(" << Quote(url) << ");"
        << "} catch(err) {}";
      parent_->doJavaScript(stream.str());
    }

    return *this;
  }


} // namespace MapBox