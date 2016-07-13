#include "BackgroundLayer.h"
#include <sstream>

namespace MapBox {

  BackgroundLayer::BackgroundLayer()
  {
    setType(LT_BACKGROUND);
    color_.setRgb(0, 0, 0, 255);
  }

  BackgroundLayer & BackgroundLayer::color(const Wt::WColor & value) {
    color_ = value;
    setPaint("background-color", "'" + value.cssText() + "'");
    return *this;
  }

  const Wt::WColor & BackgroundLayer::color() const {
    return color_;
  }

  BackgroundLayer & BackgroundLayer::pattern(const std::string & value) {
    setPaint("background-pattern", value);
    return *this;
  }

  std::string BackgroundLayer::pattern() const {
    return getPaint("background-pattern");
  }

  BackgroundLayer & BackgroundLayer::opacity(int value) {
    setPaint("background-opacity", std::to_string(value));
    return *this;
  }

  int BackgroundLayer::opacity() const {
    std::string result = getPaint("background-opacity");
    if (!result.empty()) {
      return std::stof(result);
    }
    return 1.0f;
  }


} // namespace MapBox
