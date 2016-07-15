#pragma once
#include "Layer.h"
#include "Enumerations.h"
#include "Coordinate.h"
#include "Definitions.h"

namespace MapBox {

  class LineLayer : public Layer {
  public:
    LineLayer();

    LineLayer & cap       (CAP   value); CAP   cap       () C { return cap_       ; } // The display of line endings. Defaults to butt.
    LineLayer & join      (JOIN  value); JOIN  join      () C { return join_      ; } // The display of lines when joining. Defaults to miter.
    LineLayer & miterLimit(float value); float miterLimit() C { return miterLimit_; } // Used to automatically convert miter joins to bevel joins for sharp angles. Defaults to 2.
    LineLayer & roundLimit(float value); float roundLimit() C { return roundLimit_; } // Used to automatically convert round joins to miter joins for shallow angles. Defaults to 1.05.

    LineLayer & opacity  (float value); float opacity  () C { return opacity_  ; } // The opacity at which the line will be drawn. Defaults to 1.
    LineLayer & width    (int   value); int   width    () C { return width_    ; } // Stroke thickness. Defaults to 1.
    LineLayer & gapWidth (int   value); int   gapWidth () C { return gapWidth_ ; } // Draws a line casing outside of a line’s actual path. Value indicates the width of the inner gap. Defaults to 0.
    LineLayer & offset   (int   value); int   offset   () C { return offset_   ; } // The line’s offset perpendicular to its direction. Values may be positive or negative, where positive indicates “rightwards” (if you were moving in the direction of the line) and negative indicates “leftwards.” Defaults to 0.
    LineLayer & blur     (int   value); int   blur     () C { return blur_     ; } // Blur applied to the line, in pixels. Defaults to 0.
    LineLayer & dashArray(float value); float dashArray() C { return dashArray_; } // Specifies the lengths of the alternating dashes and gaps that form the dash pattern. The lengths are later scaled by the line width. To convert a dash length to pixels, multiply the length by the current line width. 

    LineLayer & pattern  (C Wt::WString & value); C Wt::WString & pattern() C { return pattern_; } // Name of image in sprite to use for drawing image lines. For seamless patterns, image width must be a factor of two (2, 4, 8, …, 512).
    LineLayer & color    (C Wt::WColor  & value); C Wt::WColor  & color  () C { return color_  ; } // The color with which the line will be drawn. Defaults to black.

    LineLayer & translate(C Coordinate & offset, ANCHOR anchor = ANCHOR::Map); // The geometry’s offset. Values are [x, y] where negatives indicate left and up, respectively. Anchor controls whether the translation is relative to the map (north) or viewport (screen).
    C Coordinate & translation() C { return translate_; }
    ANCHOR anchor() C { return anchor_; }

  private:
    CAP        cap_      ;
    JOIN       join_     ;
    Wt::WColor color_    ;
    Coordinate translate_;
    ANCHOR     anchor_   ;
    float miterLimit_, roundLimit_, opacity_, dashArray_;
    int width_, gapWidth_, offset_, blur_;
    Wt::WString pattern_;
  };

}