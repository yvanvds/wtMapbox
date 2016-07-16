#include "GeoJSONSource.h"
#include <Wt/Json/Serializer>

namespace MapBox {

  GeoJSONSource::GeoJSONSource() 
    : Source(SOURCETYPE::GeoJSON)
    , data_(nullptr)
    , maxZoom_(18)
    , cluster_(false)
  {

  }

  GeoJSONSource & GeoJSONSource::sourceData(GeoJSONObject * data) {
    data_ = data;
    return *this;
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

  Wt::WString GeoJSONSource::render() {
    std::stringstream stream;
    stream
      << "'" << id_ << "', {\n"
      << "  type: 'geojson',\n";

    if (data_) {
      stream << "  data: " << Wt::Json::serialize(data_->getObject()) << ",\n";
    }
    else {
      stream << "  data: '" << url_ << "',\n";
    }
    stream 
      << "  cluster: " << (cluster_ ? "true" : "false") << ",\n"
      << "  clusterMaxZoom: " << clusterMaxZoom_ << ",\n"
      << "  clusterRadius: " << clusterRadius_ << "\n"
      << "}";
    return stream.str();
  }

} // namespace MapBox