#pragma once

#include <string>
#include <vector>

namespace MapBox {
  class Coordinate;

  enum SOURCETYPE {
    ST_VECTOR,
    ST_RASTER,
    ST_GEOJSON,
    ST_IMAGE,
    ST_VIDEO,
  };

  class Source
  {
  public:
    Source(SOURCETYPE type);
    
    SOURCETYPE type() { return type_; }
    const std::string & id() { return id_; }
    
    virtual std::string render() = 0;

  protected:
    SOURCETYPE type_;
    std::string id_;

  };

} // namespace MapBox
