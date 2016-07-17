#include "stdafx.h"
#include "CircleLayer.h"
#include "Conversions.h"
#include <Wt/Json/Serializer>

namespace MapBox {

  CircleLayer::CircleLayer()
  {
    type(LAYERTYPE::Circle);
    color_.setRgb(0,0,0,255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
    radius_ = 5;
    blur_ = 0;
    opacity_ = 1;
  }


  CircleLayer & CircleLayer::radius(int value) {
    radius_ = value;
    setPaint("circle-radius", ToScript(value));
    return *this;
  }


  CircleLayer & CircleLayer::color(const Wt::WColor & value) {
    color_ = value; 
    setPaint("circle-color", ToScript(value));
    return *this;
  }

  CircleLayer & CircleLayer::blur(float value) {
    blur_ = value;
    setPaint("circle-blur", ToScript(value));
    return *this;
  }

  CircleLayer & CircleLayer::opacity(float value) {
    opacity_ = value;
    setPaint("circle-opacity", ToScript(value));
    return *this;
  }

  CircleLayer & CircleLayer::translate(const Coordinate & offset, ANCHOR anchor) {
    setPaint("circle-translate", ToScript(offset));
    setPaint("circle-translate-anchor", ToScript(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }

  CircleLayer & CircleLayer::radius(C Wt::Json::Object & obj) {
    jsonRadius = Wt::Json::serialize(obj);
    setPaint("circle-radius", jsonRadius);
    return *this;
  }

  CircleLayer & CircleLayer::color(C Wt::Json::Object & obj) {
    jsonColor = Wt::Json::serialize(obj);
    setPaint("circle-color", jsonColor);
    Wt::log(jsonColor.toUTF8());
    return *this;
  }

} // namespace MapBox
