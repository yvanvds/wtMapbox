#include "stdafx.h"
#include "CircleLayer.h"
#include "Conversions.h"

namespace MapBox {

  CircleLayer::CircleLayer()
  {
    setType(LAYERTYPE::Circle);
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

} // namespace MapBox
