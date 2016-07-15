#include "BackgroundLayer.h"
#include "Conversions.h"

namespace MapBox {

  BackgroundLayer::BackgroundLayer()
  {
    setType(LAYERTYPE::Background);
    color_.setRgb(0, 0, 0, 255);
    opacity_ = 1;
  }

  BackgroundLayer & BackgroundLayer::color(const Wt::WColor & value) {
    color_ = value;
    setPaint("background-color", ToScript(value));
    return *this;
  }

  BackgroundLayer & BackgroundLayer::pattern(const Wt::WString & value) {
    pattern_ = value;
    setPaint("background-pattern", value);
    return *this;
  }

  BackgroundLayer & BackgroundLayer::opacity(int value) {
    opacity_ = value;
    setPaint("background-opacity", ToScript(value));
    return *this;
  }


} // namespace MapBox
