#include "RasterLayer.h"
#include "Conversions.h"

namespace MapBox {

  RasterLayer::RasterLayer() {
    type(LAYERTYPE::Raster);
    opacity_ = 1;
    hueRotate_ = 0;
    brightnessMin_ = 0;
    brightnessMax_ = 1;
    saturation_ = 0;
    contrast_ = 0;
    fadeDuration_ = 300;
  }

  RasterLayer & RasterLayer::opacity(float value) {
    opacity_ = value;
    setPaint("raster-opacity", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::hueRotate(float value) {
    hueRotate_ = value;
    setPaint("raster-hue-rotate", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::brightnessMin(float value) {
    brightnessMin_ = value;
    setPaint("raster-brightness-min", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::brightnessMax(float value) {
    brightnessMax_ = value;
    setPaint("raster-brightness-max", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::saturation(float value) {
    saturation_ = value;
    setPaint("raster-saturation", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::contrast(float value) {
    contrast_ = value;
    setPaint("raster-contrast", ToScript(value));
    return *this;
  }

  RasterLayer & RasterLayer::fadeDuration(float value) {
    fadeDuration_ = value;
    setPaint("raster-fade-duration", ToScript(value));
    return *this;
  }
}
