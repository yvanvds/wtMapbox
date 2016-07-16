#include "GeoJSON.h"
#include <Wt/Json/Value>
#include <Wt/Json/Array>

using namespace Wt;

namespace MapBox {

  GeoJSONObject::GeoJSONObject(C std::string & type) {
    object["type"] = Json::Value(type);
  }

  void GeoJSONObject::setBoundingBox(C Bounds & bounds) {
    object["bbox"] = Json::Value(Json::ArrayType);
    Json::Array& arr = (Json::Array &)object.get("bbox");
    if (!arr.empty()) arr.clear();
    arr.push_back(bounds.min.longitude());
    arr.push_back(bounds.min.latitude());
    arr.push_back(bounds.max.longitude());
    arr.push_back(bounds.max.latitude());
  }

  GGeometryObject::GGeometryObject(C std::string & type)
    : GeoJSONObject(type)
  {
    object["coordinates"] = Json::Value(Json::ArrayType);
  }

  void GGeometryObject::addCoordinate(C Coordinate & pos) {
    Json::Array & arr = object["coordinates"];
    arr.push_back(Json::Value(Json::ArrayType));
    Json::Array & back = (Json::Array &)arr.back();
    back.push_back(pos.longitude());
    back.push_back(pos.latitude());
  }

  void GGeometryObject::clearCoordinates() {
    Json::Array & arr = object["coordinates"];
    arr.clear();
  }

  GPoint::GPoint() : GGeometryObject("Point") {
    object["coordinates"] = Json::Value(Json::ArrayType);
  }

  void GPoint::set(C Coordinate & pos) {
    Json::Array& arr = object["coordinates"];
    if (!arr.empty()) arr.clear();
    arr.push_back(pos.longitude());
    arr.push_back(pos.latitude());
  }

  void GPoint::set(float latitude, float longitude) {
    set(Coordinate(latitude, longitude));
  }

  GMultiPoint::GMultiPoint() : GGeometryObject("MultiPoint") {}

  GMultiPoint & GMultiPoint::add(C Coordinate & pos) {
    addCoordinate(pos);
    return *this;
  }

  GMultiPoint & GMultiPoint::add(float latitude, float longitude) {
    addCoordinate(Coordinate(latitude, longitude));
    return *this;
  }

  GMultiPoint & GMultiPoint::clear() {
    clearCoordinates();
    return *this;
  }

  GLineString::GLineString() : GGeometryObject("LineString") {}

  GLineString & GLineString::add(C Coordinate & pos) {
    addCoordinate(pos);
    return *this;
  }

  GLineString & GLineString::clear() {
    clearCoordinates();
    return *this;
  }

  GMultiLineString::GMultiLineString() : GGeometryObject("MultiLineString") {}

  GMultiLineString & GMultiLineString::add(C Coordinate & pos, int line) {
    Json::Array & arr = object["coordinates"];
    while (arr.size() < line + 1) {
      arr.emplace_back(Json::Value(Json::ArrayType));
    }

    Json::Array & cur = arr[line];
    cur.emplace_back(Json::Value(Json::ArrayType));
    
    ((Json::Array&)(cur.back())).push_back(pos.longitude());
    ((Json::Array&)(cur.back())).push_back(pos.latitude ());
    return *this;
  }

  GMultiLineString & GMultiLineString::clear(int line) {
    Json::Array & arr = object["coordinates"];
    if (line < arr.size()) {
      arr.erase(arr.begin() + line);
    }
    return *this;
  }

  GMultiLineString & GMultiLineString::clear() {
    Json::Array & arr = object["coordinates"];
    arr.clear();
    return *this;
  }

  GPolygon::GPolygon() : GGeometryObject("Polygon") {}

  GPolygon & GPolygon::add(C Coordinate & pos, int ring) {
    Json::Array & arr = object["coordinates"];
    while (arr.size() < ring + 1) {
      arr.emplace_back(Json::Value(Json::ArrayType));
    }

    Json::Array & cur = arr[ring];
    cur.emplace_back(Json::Value(Json::ArrayType));

    ((Json::Array&)(cur.back())).push_back(pos.longitude());
    ((Json::Array&)(cur.back())).push_back(pos.latitude());
    return *this;
  }

  GPolygon & GPolygon::clear(int ring) {
    Json::Array & arr = object["coordinates"];
    if (ring < arr.size()) {
      arr.erase(arr.begin() + ring);
    }
    return *this;
  }

  GPolygon & GPolygon::clear() {
    Json::Array & arr = object["coordinates"];
    arr.clear();
    return *this;
  }

  GMultiPolygon::GMultiPolygon() : GGeometryObject("MultiPolygon") {}

  GMultiPolygon & GMultiPolygon::add(C Coordinate & pos, int ring, int polygon) {
    Json::Array & arr = object["coordinates"];

    while (arr.size() < polygon + 1) {
      arr.emplace_back(Json::Value(Json::ArrayType));
    }

    Json::Array & poly = arr[polygon];

    while (poly.size() < ring + 1) {
      poly.emplace_back(Json::Value(Json::ArrayType));
    }

    Json::Array & cur = poly[ring];

    cur.emplace_back(Json::Value(Json::ArrayType));

    ((Json::Array&)(cur.back())).push_back(pos.longitude());
    ((Json::Array&)(cur.back())).push_back(pos.latitude());
    return *this;
  }

  GMultiPolygon & GMultiPolygon::clear(int polygon) {
    Json::Array & arr = object["coordinates"];
    if (polygon < arr.size()) {
      arr.erase(arr.begin() + polygon);
    }
    return *this;
  }

  GMultiPolygon & GMultiPolygon::clear() {
    Json::Array & arr = object["coordinates"];
    arr.clear();
    return *this;
  }

  GGeometryCollection::GGeometryCollection()
    : GeoJSONObject("GeometryCollection")
  {
    object["geometries"] = Json::Value(Json::ArrayType);
  }

  GGeometryCollection & GGeometryCollection::add(C GGeometryObject & obj) {
    Json::Array & arr = object["geometries"];
    arr.emplace_back(Json::Value(Json::ObjectType));
    ((Json::Object &)(arr.back())) = obj.getObject();
    return *this;
  }

  GFeature::GFeature()
    : GeoJSONObject("Feature")
  {
    object["geometry"] = Json::NullType;
    object["properties"] = Json::NullType;
  }

  GFeature & GFeature::id(C std::string & value) {
    object["id"] = Json::Value(value);
    return *this;
  }

  GFeature & GFeature::geometry(C GGeometryObject & obj) {
    object["geometry"] = Json::Value(Json::ObjectType);
    ((Json::Object&)object["geometry"]) = obj.getObject();
    return *this;
  }

  GFeature & GFeature::geometry(C GGeometryCollection& obj) {
    object["geometry"] = Json::Value(Json::ObjectType);
    ((Json::Object&)object["geometry"]) = obj.getObject();
    return *this;
  }

  GFeature & GFeature::properties(C Json::Object & obj) {
    object["properties"] = Json::Value(Json::ObjectType);
    ((Json::Object&)object["properties"]) = obj;
    return *this;
  }

  GFeatureCollection::GFeatureCollection()
    : GeoJSONObject("FeatureCollection")
  {
    object["features"] = Json::Value(Json::ArrayType);
  }

  GFeatureCollection & GFeatureCollection::add(C GFeature & feature) {
    Json::Array & arr = object["features"];
    arr.emplace_back(Json::Value(Json::ObjectType));
    ((Json::Object &)(arr.back())) = feature.getObject();
    return *this;
  }
}