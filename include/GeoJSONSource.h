#pragma once

#include <string>
#include "Source.h"

namespace MapBox {

  class GeoJSONSource : public Source
  {
  public:
    GeoJSONSource();

    
    GeoJSONSource & setMaxZoom(int level);
    // maxClusterZoom defaults to maxZoom - 1
    GeoJSONSource & setCluster(int radius = 50, int maxClusterZoom = -1);
    GeoJSONSource & disableCluster();

    C Wt::WString & url() { return url_; }

    int  maxZoom       () { return maxZoom_       ; }
    bool isCluster     () { return cluster_       ; }
    int  clusterRadius () { return clusterRadius_ ; }
    int  clusterMaxZoom() { return clusterMaxZoom_; }

    virtual Wt::WString render();

  private:
    
    int maxZoom_;
    bool cluster_;
    int clusterRadius_;
    int clusterMaxZoom_;
  };

} // namespace MapBox
