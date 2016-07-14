#pragma once
#include "Layer.h"
#include "Enumerations.h"
#include "Coordinate.h"
#include "Definitions.h"

namespace MapBox {

  class FillLayer : public Layer
  {
  public:
    FillLayer();
    
    FillLayer & antialias   (  bool         value);   bool         antialias   () C { return antialias_; } // Whether or not the fill should be antialiased. Defaults to true
    FillLayer & opacity     (  float        value);   float        opacity     () C { return opacity_  ; } // The opacity of the entire fill layer.In contrast to the fill - color, this value will also affect the 1px stroke around the fill, if the stroke is used. Defaults to 1.
    FillLayer & color       (C Wt::WColor & value); C Wt::WColor & color       () C { return color_    ; } // The color of the filled part of this layer. This color can be specified as rgba with an alpha component and the color’s opacity will not affect the opacity of the 1px stroke, if it is used. Defaults to black.
    FillLayer & outlineColor(C Wt::WColor & value); C Wt::WColor & outlineColor() C;                       // The outline color of the fill. Matches the value of fill-color if unspecified.
    
    FillLayer & translate(C Coordinate & offset, ANCHOR anchor = ANCHOR::Map); // The geometry’s offset. Values are [x, y] where negatives indicate left and up, respectively. Anchor controls whether the translation is relative to the map (north) or viewport (screen).
    const Coordinate & translation() C { return translate_; }
    ANCHOR anchor() C { return anchor_; }

  private:
    Wt::WColor color_       ;
    Wt::WColor outlineColor_;
    Coordinate translate_   ;
    ANCHOR     anchor_      ;
    bool       antialias_   ;
    float      opacity_     ;

    bool outlineColorSet;
  };

}

