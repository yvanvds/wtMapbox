#pragma once
#include "Layer.h"
#include "Definitions.h"

namespace MapBox {

  class BackgroundLayer : public Layer
  {
  public:
    BackgroundLayer();
    
    BackgroundLayer & color  (C Wt::WColor  & value); C Wt::WColor  & color  () C { return color_  ; } // The color with which the background will be drawn. Defaults to black.
    BackgroundLayer & pattern(C Wt::WString & value);   Wt::WString   pattern() C { return pattern_; } // Name of image in sprite to use for drawing an image background. For seamless patterns, image width and height must be a factor of two (2, 4, 8, …, 512).
    BackgroundLayer & opacity(  int           value);   int           opacity() C { return opacity_; } // The opacity at which the background will be drawn. Defaults to 1.

  private:
    Wt::WColor color_;
    Wt::WString pattern_;
    int opacity_;
  };

} // namespace MapBox

