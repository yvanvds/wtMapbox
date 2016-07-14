#include "GeoJSONSource.h"

namespace MapBox {

  GeoJSONSource::GeoJSONSource() 
    : Source(SOURCETYPE::GeoJSON)
    , maxZoom_(18)
    , cluster_(false)
  {

  }

  

  GeoJSONSource & GeoJSONSource::setMaxZoom(int level) {
    maxZoom_ = level;
    return *this;
  }

  GeoJSONSource & GeoJSONSource::setCluster(int radius, int maxClusterZoom) {
    cluster_ = true;
    clusterRadius_ = radius;
    clusterMaxZoom_ = maxClusterZoom;
    return *this;
  }

  GeoJSONSource & GeoJSONSource::disableCluster() {
    cluster_ = false;
    return *this;
  }

  std::string GeoJSONSource::render() {
    std::stringstream stream;
    stream
      << "'" << id_ << "', {\n"
      << "  type: 'geojson',\n"
      << "  data: '" << url_ << "',\n"
      << "  cluster: " << (cluster_ ? "true" : "false") << ",\n"
      << "  clusterMaxZoom: " << clusterMaxZoom_ << ",\n"
      << "  clusterRadius: " << clusterRadius_ << "\n"
      << "}";
    return stream.str();
  }

} // namespace MapBox