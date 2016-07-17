#include "stdafx.h"
#include "FillLayer.h"
#include "Conversions.h"

namespace MapBox {

  FillLayer::FillLayer()
  {
    type(LAYERTYPE::Fill);
    color_.setRgb(0, 0, 0, 255);
    outlineColor_.setRgb(0, 0, 0, 255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
    antialias_ = true;
    opacity_ = 1;

    outlineColorSet = false;
  }

  FillLayer & FillLayer::antialias(bool value)
  {
    antialias_ = value;
    setPaint("fill-antialias", ToScript(value));
    return *this;
  }

  FillLayer & FillLayer::opacity(float value)
  {
    opacity_ = value;
    setPaint("fill-opacity", ToScript(value));
    return *this;
  }

  FillLayer & FillLayer::color(const Wt::WColor & value)
  {
    color_ = value;
    setPaint("fill-color", ToScript(value));
    return *this;
  }

  FillLayer & FillLayer::outlineColor(const Wt::WColor & value)
  {
    outlineColorSet = true;
    outlineColor_ = value;
    setPaint("fill-outline-color", ToScript(value));
    return *this;
  }

  const Wt::WColor & FillLayer::outlineColor() const
  {
    // the outline color matches the fill color if not specified
    if (!outlineColorSet) {
      return color_;
    }
    return outlineColor_;
  }

  FillLayer & FillLayer::translate(const Coordinate & offset, ANCHOR anchor)
  {
    setPaint("fill-translate", ToScript(offset));
    setPaint("fill-translate-anchor", ToScript(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }



}