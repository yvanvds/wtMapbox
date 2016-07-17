#include "LineLayer.h"
#include "Conversions.h"

namespace MapBox {



  LineLayer::LineLayer()
  {
    type(LAYERTYPE::Line);
    cap_ = CAP::Butt;
    join_ = JOIN::Miter;
    color_.setRgb(0, 0, 0, 255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
    miterLimit_ = 2;
    roundLimit_ = 1.05f;
    opacity_ = 1;
    width_ = 1;
    gapWidth_ = 0;
    offset_ = 0;
    blur_ = 0;
    dashArray_ = 0;
  }

  LineLayer & LineLayer::cap(CAP value)
  {
    setLayout("line-cap", ToScript(value));
    cap_ = value;
    return *this;
  }

  LineLayer & LineLayer::join(JOIN value)
  {
    setLayout("line-join", ToScript(value));
    join_ = value;
    return *this;
  }

  LineLayer & LineLayer::miterLimit(float value)
  {
    miterLimit_ = value;
    setLayout("line-miter-limit", ToScript(value));
    return *this;
  }


  LineLayer & LineLayer::roundLimit(float value)
  {
    roundLimit_ = value;
    setLayout("line-round-limit", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::opacity(float value)
  {
    opacity_ = value;
    setPaint("line-opacity", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::width(int value)
  {
    width_ = value;
    setPaint("line-width", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::gapWidth(int value)
  {
    gapWidth_ = value;
    setPaint("line-gap-width", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::offset(int value)
  {
    offset_ = value;
    setPaint("line-offset", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::blur(int value)
  {
    blur_ = value;
    setPaint("line-blur", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::dashArray(float value)
  {
    dashArray_ = value;
    setPaint("line-dasharray", ToScript(value));
    return *this;
  }

  LineLayer & LineLayer::pattern(const Wt::WString & value)
  {
    pattern_ = value;
    setPaint("line-pattern", value);
    return *this;
  }

  LineLayer & LineLayer::color(const Wt::WColor & value)
  {
    color_ = value;
    setPaint("line-color", ToScript(value));
    return *this;
  }


  LineLayer & LineLayer::translate(const Coordinate & offset, ANCHOR anchor)
  {
    setPaint("line-translate", ToScript(offset));
    setPaint("line-translate-anchor", ToScript(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }



}