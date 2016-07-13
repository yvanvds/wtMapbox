#pragma once

#include <string>
#include "Source.h"

namespace MapBox {

  class GeoJSONSource : public Source
  {
  public:
    GeoJSONSource();

    GeoJSONSource & setFromURL(const std::string & url);
    GeoJSONSource & setMaxZoom(int level);
    // maxClusterZoom defaults to maxZoom - 1
    GeoJSONSource & setCluster(int radius = 50, int maxClusterZoom = -1);
    GeoJSONSource & disableCluster();

    const std::string & url() { return url_; }

    int  maxZoom       () { return maxZoom_       ; }
    bool isCluster     () { return cluster_       ; }
    int  clusterRadius () { return clusterRadius_ ; }
    int  clusterMaxZoom() { return clusterMaxZoom_; }

    virtual std::string render();

  private:
    std::string url_;
    int maxZoom_;
    bool cluster_;
    int clusterRadius_;
    int clusterMaxZoom_;
  };

} // namespace MapBox
