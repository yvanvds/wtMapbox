#include "stdafx.h"
#include "FillLayer.h"

namespace MapBox {

  FillLayer::FillLayer()
  {
    setType(LT_FILL);
    color_.setRgb(0, 0, 0, 255);
    outlineColor_.setRgb(0, 0, 0, 255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
  }

  FillLayer & FillLayer::antialias(bool value)
  {
    if (value) setPaint("fill-antialias", "true" );
    else       setPaint("fill-antialias", "false");
    return *this;
  }

  bool FillLayer::antialias() const
  {
    std::string result = getPaint("fill-antialias");
    if (result.empty()) return true; // default value
    if (result == "true") return true;
    return false;
  }

  FillLayer & FillLayer::opacity(float value)
  {
    setPaint("fill-opacity", std::to_string(value));
    return *this;
  }

  float FillLayer::opacity() const
  {
    std::string result = getPaint("fill-opacity");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 1.0f;
  }

  FillLayer & FillLayer::color(const Wt::WColor & value)
  {
    color_ = value;
    setPaint("fill-color", "'" + value.cssText() + "'");
    return *this;
  }

  const Wt::WColor & FillLayer::color() const
  {
    return color_;
  }

  FillLayer & FillLayer::outlineColor(const Wt::WColor & value)
  {
    outlineColor_ = value;
    setPaint("fill-outline-color", "'" + value.cssText() + "'");
    return *this;
  }

  const Wt::WColor & FillLayer::outlineColor() const
  {
    // the outline color matches the fill color if not specified
    if (outlineColor_ == Wt::WColor(0, 0, 0, 255)) {
      return color_;
    }
    return outlineColor_;
  }

  FillLayer & FillLayer::translate(const Coordinate & offset, ANCHOR anchor)
  {
    setPaint("fill-translate", "[" + std::to_string(offset.latitude()) + ", " + std::to_string(offset.longitude()) + "]");
    setPaint("fill-translate-anchor", AnchorToString(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }



}