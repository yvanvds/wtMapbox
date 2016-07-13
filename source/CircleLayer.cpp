#include "stdafx.h"
#include "CircleLayer.h"

namespace MapBox {

  CircleLayer::CircleLayer()
  {
    setType(LT_CIRCLE);
    color_.setRgb(0,0,0,255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
  }


  CircleLayer & CircleLayer::radius(int value) {
    setPaint("circle-radius", std::to_string(value));
    return *this;
  }

  int CircleLayer::radius() const
  {
    std::string result = getPaint("circle-radius");
    if (result.empty()) {
      return 5; // default value
    }
    else {
      return std::stoi(result);
    }
    return 0;
  }

  CircleLayer & CircleLayer::color(const Wt::WColor & value) {
    color_ = value; 
    setPaint("circle-color", "'" + value.cssText() + "'");
    return *this;
  }

  const Wt::WColor & CircleLayer::color() const
  {
    return color_;
  }

  CircleLayer & CircleLayer::blur(float value) {
    setPaint("circle-blur", std::to_string(value));
    return *this;
  }

  float CircleLayer::blur() const
  {
    std::string result = getPaint("circle-blur");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 0.0f;
  }

  CircleLayer & CircleLayer::opacity(float value) {
    setPaint("circle-opacity", std::to_string(value));
    return *this;
  }

  float CircleLayer::opacity() const
  {
    std::string result = getPaint("circle-opacity");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 1.0f;
  }

  CircleLayer & CircleLayer::translate(const Coordinate & offset, ANCHOR anchor) {
    setPaint("circle-translate", "[" + std::to_string(offset.latitude()) + ", " + std::to_string(offset.longitude()) + "]");
    setPaint("circle-translate-anchor", AnchorToString(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }

} // namespace MapBox
