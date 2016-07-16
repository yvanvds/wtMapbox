#pragma once

/*
  This is a quick en dirty implementation for GeoJSON objects. Not really fit for
  big objects. It is based on the Wt Json object. Some problems are:
  - Collections make copies when elements are added. Pointers would be a lot 
    more efficient.
  - It would be better to add simple objects to complex ones, like adding GPoint to 
    GMultipont, but this would not result in the correct syntax when serialized. 
    (Which means the Wt::Json::Serialize function cannot be used.)
*/

#include <Wt/Json/Object>
#include <string>
#include "Definitions.h"
#include "Coordinate.h"

namespace MapBox {

  class GeoJSONObject {
  public:
    GeoJSONObject(C std::string & type);
    
    void setBoundingBox(C Bounds & bounds);
    C Wt::Json::Object & getObject() C { return object; }
  protected:
    Wt::Json::Object object;
  };

  class GGeometryObject : public GeoJSONObject {
  public:
    GGeometryObject(C std::string & type);

  protected:
    void addCoordinate(C Coordinate & pos);
    void clearCoordinates();
  };

  class GPoint : public GGeometryObject {
  public:
    GPoint();
    void set(C Coordinate & pos);
    void set(float latitude, float longitude);
  };

  class GMultiPoint : public GGeometryObject {
  public:
    GMultiPoint();
    GMultiPoint & add(C Coordinate & pos);
    GMultiPoint & add(float latitude, float longitude);
    GMultiPoint & clear();
  };

  class GLineString : public GGeometryObject {
  public:
    GLineString();
    GLineString & add(C Coordinate & pos);
    GLineString & clear();
  };

  class GMultiLineString : public GGeometryObject {
  public:
    GMultiLineString();
    GMultiLineString & add(C Coordinate & pos, int line);
    GMultiLineString & clear(int line);
    GMultiLineString & clear();
  };

  class GPolygon : public GGeometryObject {
  public:
    GPolygon();
    GPolygon & add(C Coordinate & pos, int ring = 0);
    GPolygon & clear(int ring);
    GPolygon & clear();
  };

  class GMultiPolygon : public GGeometryObject {
  public:
    GMultiPolygon();
    GMultiPolygon & add(C Coordinate & pos, int ring = 0, int polygon = 0);
    GMultiPolygon & clear(int polygon);
    GMultiPolygon & clear();
  };

  class GGeometryCollection : public GeoJSONObject {
  public:
    GGeometryCollection();
    GGeometryCollection & add(C GGeometryObject & obj);
  };

  class GFeature : public GeoJSONObject {
  public:
    GFeature();
    GFeature & id(C std::string & value);
    GFeature & geometry(C GGeometryObject & obj);
    GFeature & geometry(C GGeometryCollection& obj);
    GFeature & properties(C Wt::Json::Object & obj);
  };

  class GFeatureCollection : public GeoJSONObject {
  public:
    GFeatureCollection();
    GFeatureCollection & add(C GFeature & feature);
  };
}