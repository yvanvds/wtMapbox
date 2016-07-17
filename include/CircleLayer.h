#pragma once
#include "Layer.h"
#include "Coordinate.h"
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {


  class CircleLayer : public Layer
  {
  public:
    CircleLayer();

    // paint properties
    CircleLayer & radius (  int          value);   int          radius () C { return radius_ ; } // Circle radius. Defaults to 5.
    CircleLayer & color  (C Wt::WColor & value); C Wt::WColor & color  () C { return color_  ; } // The color of the circle. Defaults to black.
    CircleLayer & blur   (  float        value);   float        blur   () C { return blur_   ; } // Amount to blur the circle. 1 blurs the circle such that only the centerpoint is full opacity. Defaults to 0.
    CircleLayer & opacity(  float        value);   float        opacity() C { return opacity_; } // The opacity at which the circle will be drawn. Defaults to 1.

    CircleLayer & translate(C Coordinate & offset, ANCHOR anchor = ANCHOR::Map); // The geometry’s offset. Values are [x, y] where negatives indicate left and up, respectively. Anchor controls whether the translation is relative to the map (north) or viewport (screen).
    C Coordinate & translation() C { return translate_; }
    ANCHOR anchor() C { return anchor_; }

    // more advanced options are possible when using json objects. See mapbox api for more info
    CircleLayer & radius(C Wt::Json::Object & obj);
    CircleLayer & color (C Wt::Json::Object & obj);

  private:

    // properties to remember for easy retrieval
    Wt::WColor color_    ;
    Coordinate translate_;
    ANCHOR     anchor_   ;
    int        radius_   ;
    float      blur_     ;
    float      opacity_  ;

    Wt::WString jsonRadius, jsonColor;
  };

} // namespace MapBox

