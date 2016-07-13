#include "LineLayer.h"

namespace MapBox {



  LineLayer::LineLayer()
  {
    setType(LT_LINE);
    cap_ = CAP::Butt;
    join_ = JOIN::Miter;
    color_.setRgb(0, 0, 0, 255);
    translate_ = Coordinate(0, 0);
    anchor_ = ANCHOR::Map;
  }

  LineLayer & LineLayer::cap(CAP value)
  {
    setLayout("line-cap", CapToString(value));
    cap_ = value;
    return *this;
  }

  CAP LineLayer::cap() const
  {
    return cap_;
  }

  LineLayer & LineLayer::join(JOIN value)
  {
    setLayout("line-join", JoinToString(value));
    join_ = value;
    return *this;
  }

  JOIN LineLayer::join() const
  {
    return join_;
  }

  LineLayer & LineLayer::miterLimit(float value)
  {
    setLayout("line-miter-limit", std::to_string(value));
    return *this;
  }

  float LineLayer::miterLimit() const
  {
    std::string result = getLayout("line-miter-limit");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 2.0f;
  }

  LineLayer & LineLayer::roundLimit(float value)
  {
    setLayout("line-round-limit", std::to_string(value));
    return *this;
  }

  float LineLayer::roundLimit() const
  {
    std::string result = getLayout("line-round-limit");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 1.05f;
  }

  LineLayer & LineLayer::opacity(float value)
  {
    setPaint("line-opacity", std::to_string(value));
    return *this;
  }

  float LineLayer::opacity() const
  {
    std::string result = getPaint("line-opacity");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 1.0f;
  }

  LineLayer & LineLayer::width(int value)
  {
    setPaint("line-width", std::to_string(value));
    return *this;
  }

  int LineLayer::width() const
  {
    std::string result = getPaint("line-width");
    if (!result.empty()) {
      return std::stoi(result);
    }
    return 1;
  }

  LineLayer & LineLayer::gapWidth(int value)
  {
    setPaint("line-gap-width", std::to_string(value));
    return *this;
  }

  int LineLayer::gapWidth() const
  {
    std::string result = getPaint("line-gap-width");
    if (!result.empty()) {
      return std::stoi(result);
    }
    return 0;
  }

  LineLayer & LineLayer::offset(int value)
  {
    setPaint("line-offset", std::to_string(value));
    return *this;
  }

  int LineLayer::offset() const
  {
    std::string result = getPaint("line-offset");
    if (!result.empty()) {
      return std::stoi(result);
    }
    return 0;
  }

  LineLayer & LineLayer::blur(int value)
  {
    setPaint("line-blur", std::to_string(value));
    return *this;
  }

  int LineLayer::blur() const
  {
    std::string result = getPaint("line-blur");
    if (!result.empty()) {
      return std::stoi(result);
    }
    return 0;
  }

  LineLayer & LineLayer::dashArray(float value)
  {
    setPaint("line-dasharray", std::to_string(value));
    return *this;
  }

  float LineLayer::dashArray() const
  {
    std::string result = getPaint("line-dasharray");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 0.0f;
  }

  LineLayer & LineLayer::pattern(const std::string & value)
  {
    setPaint("line-pattern", value);
    return *this;
  }

  std::string LineLayer::pattern() const
  {
    return getPaint("line-pattern");
  }

  LineLayer & LineLayer::color(const Wt::WColor & value)
  {
    color_ = value;
    setPaint("line-color", "'" + value.cssText() + "'");
    return *this;
  }

  const Wt::WColor & LineLayer::color() const
  {
    return color_;
  }

  LineLayer & LineLayer::translate(const Coordinate & offset, ANCHOR anchor)
  {
    setPaint("line-translate", "[" + std::to_string(offset.latitude()) + ", " + std::to_string(offset.longitude()) + "]");
    setPaint("line-translate-anchor", AnchorToString(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }



}