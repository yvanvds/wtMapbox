#pragma once

#include <string>
#include "Source.h"
#include "GeoJSON.h"

namespace MapBox {

  class GeoJSONSource : public Source
  {
  public:
    GeoJSONSource();

    GeoJSONSource & set(C Wt::WString   & url );
    GeoJSONSource & set(  GeoJSONObject * data);

    GeoJSONSource & maxZoom(int level);
    GeoJSONSource & cluster(int radius = 50, int maxClusterZoom = -1);
    GeoJSONSource & disableCluster();

    C Wt::WString & url() { return url_; }

    int  maxZoom       () { return maxZoom_       ; }
    bool isCluster     () { return cluster_       ; }
    int  clusterRadius () { return clusterRadius_ ; }
    int  clusterMaxZoom() { return clusterMaxZoom_; }

    virtual Wt::WString render();

  private:
    GeoJSONObject * data_;
    int maxZoom_;
    bool cluster_;
    int clusterRadius_;
    int clusterMaxZoom_;
  };

} // namespace MapBox
