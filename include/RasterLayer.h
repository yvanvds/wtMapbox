#pragma once
#include "Layer.h"
#include "Definitions.h"

namespace MapBox {

  class RasterLayer : public Layer
  {
  public:
    RasterLayer();

    RasterLayer & opacity      (float value); float opacity      () C { return opacity_      ; } // The opacity at which the image will be drawn. Defaults to 1.
    RasterLayer & hueRotate    (float value); float hueRotate    () C { return hueRotate_    ; } // Rotates hues around the color wheel. Defaults to 0.
    RasterLayer & brightnessMin(float value); float brightnessMin() C { return brightnessMin_; } // Increase or reduce the brightness of the image. The value is the minimum brightness. Defaults to 0.
    RasterLayer & brightnessMax(float value); float brightnessMax() C { return brightnessMax_; } // Increase or reduce the brightness of the image. The value is the maximum brightness. Defaults to 1.
    RasterLayer & saturation   (float value); float saturation   () C { return saturation_   ; } // Increase or reduce the saturation of the image. Defaults to 0.
    RasterLayer & contrast     (float value); float contrast     () C { return contrast_     ; } // Increase or reduce the contrast of the image. Defaults to 0.
    RasterLayer & fadeDuration (float value); float fadeDuration () C { return fadeDuration_ ; } // Fade duration when a new tile is added. Defaults to 300.

  private:
    float opacity_;
    float hueRotate_;
    float brightnessMin_;
    float brightnessMax_;
    float saturation_;
    float contrast_;
    float fadeDuration_;
  };

}