#pragma once
#include "Layer.h"
#include "Enumerations.h"
#include "Coordinate.h"
#include "Definitions.h"

namespace MapBox {

  class SymbolLayer : public Layer {
  public :
    SymbolLayer();

    // Generic Layout properties
    SymbolLayer & placement (PLACEMENT value ); PLACEMENT placement () C { return placement_ ; } // Label placement relative to its geometry. line can only be used on LineStrings and Polygons. Defaults to point.
    SymbolLayer & spacing   (int       pixels); int       spacing   () C { return spacing_   ; } // Requires Placement::Line. Distance between two symbol anchors. Defaults to 250.
    SymbolLayer & avoidEdges(bool      value ); bool      avoidEdges() C { return avoidEdges_; } // If true, the symbols will not cross tile edges to avoid mutual collisions. Recommended in layers that don’t have enough padding in the vector tile to prevent collisions, or if it is a point symbol layer placed after a line symbol layer. Defaults to false.
    
    class Icon {
    public:
      Icon(SymbolLayer *);

      // Layout properties
      Icon & allowOverlap     (  bool          value  );   bool          allowOverlap     () C { return allowOverlap_     ; } // If true, the icon will be visible even if it collides with other previously drawn symbols. Defaults to false.
      Icon & ignorePlacement  (  bool          value  );   bool          ignorePlacement  () C { return ignorePlacement_  ; } // If true, other symbols can be visible even if they collide with the icon. Defaults to false.
      Icon & optional         (  bool          value  );   bool          optional         () C { return optional_         ; } // If true, text will display without their corresponding icons when the icon collides with other symbols and the text does not. Defaults to false. Requires icon and text.
      Icon & rotationAlignment(  ANCHOR        value  );   ANCHOR        rotationAlignment() C { return rotationAlignment_; } // Orientation of icon when map is rotated. Defaults to viewport.
      Icon & size             (  float         value  );   float         size             () C { return size_             ; } // Scale factor for icon. 1 is original size, 3 triples the size. Defaults to 1.
      Icon & image            (C Wt::WString & value  ); C Wt::WString & image            () C { return image_            ; } // A string with {tokens} replaced, referencing the data property to pull from.
      Icon & rotate           (  int           degrees);   int           rotate           () C { return rotate_           ; } // Rotates the icon clockwise. Defaults to 0.
      Icon & padding          (  int           pixels );   int           padding          () C { return padding_          ; } // Size of the additional area around the icon bounding box used for detecting symbol collisions. Defaults to 2.
      Icon & keepUpright      (  bool          value  );   bool          keepUpright      () C { return keepUpright_      ; } // If true, the icon may be flipped to prevent it from being rendered upside-down. Defaults to false.
      Icon & offset           (C Coordinate  & value  ); C Coordinate  & offset           () C { return offset_           ; } // Offset distance of icon from its anchor. Positive values indicate right and down, while negative values indicate left and up.

      // Paint properties
      Icon & opacity  (  float        value );   float        opacity  () C { return opacity_  ; } // The opacity at which the icon will be drawn. Defaults to 1.
      Icon & color    (C Wt::WColor & value ); C Wt::WColor & color    () C { return color_    ; } // The color of the icon. This can only be used with sdf icons. Defaults to black.
      Icon & haloColor(C Wt::WColor & value ); C Wt::WColor & haloColor() C { return haloColor_; } // The color of the icon’s halo. Icon halos can only be used with sdf icons. Defaults to transparent.
      Icon & haloWidth(  int          pixels);   int          haloWidth() C { return haloWidth_; } // Distance of halo to the icon outline. Defaults to 0.
      Icon & haloBlur (  int          pixels);   int          haloBlur () C { return haloBlur_ ; } // Fade out the halo towards the outside. Defaults to 0.
      
      Icon & translate(C Coordinate & offset, ANCHOR anchor = ANCHOR::Map); // Distance that the icon’s anchor is moved from its original placement. Positive values indicate right and down, while negative values indicate left and up. Anchor controls whether the translation is relative to the map (north) or viewport (screen).
      C Coordinate & translation() C{ return translate_; }
      ANCHOR anchor() C{ return anchor_; }


    private:
      bool  allowOverlap_, ignorePlacement_, optional_, keepUpright_;
      int   rotate_, padding_, haloWidth_, haloBlur_; 
      float size_, opacity_;
      Wt::WString image_;
      Coordinate  offset_, translate_;
      ANCHOR      rotationAlignment_, anchor_;
      Wt::WColor color_, haloColor_;
      
      SymbolLayer * parent;
    };

    Icon icon;

    class Text {
    public:
      Text(SymbolLayer *);
      // Layout properties
      Text & pitchAlignment   (  ANCHOR        value  );   ANCHOR        pitchAlignment   () C; // Aligns text to the plane of the viewport or the map when the map is pitched. Matches text-rotation-alignment if unspecified.
      Text & rotationAlignment(  ANCHOR        value  );   ANCHOR        rotationAlignment() C { return rotationAlignment_; } // Orientation of text when map is rotated. Defaults to viewport.
      Text & label            (C Wt::WString & value  ); C Wt::WString & label            () C { return label_            ; } // Value to use for a text label. Feature properties are specified using tokens like {field_name}.
      Text & font             (C Wt::WString & value  ); C Wt::WString & font             () C { return font_             ; } // Font stack to use for displaying text. Defaults to Open Sans Regular,Arial Unicode MS Regular.
      Text & size             (  float         pixels );   float         size             () C { return size_             ; } // Font size. Defaults to 16.
      Text & optional         (  bool          value  );   bool          optional         () C { return optional_         ; } // If true, icons will display without their corresponding text when the text collides with other symbols and the icon does not. Defaults to false.
      Text & maxWidth         (  float         em     );   float         maxWidth         () C { return maxWidth_         ; } // The maximum line width for text wrapping. Defaults to 10.
      Text & lineHeight       (  float         em     );   float         lineHeight       () C { return lineHeight_       ; } // Text leading value for multi-line text. Defaults to 1.2.
      Text & spacing          (  float         em     );   float         spacing          () C { return spacing_          ; } // Text tracking amount. Defaults to 0.
      Text & justify          (  JUSTIFY       value  );   JUSTIFY       justify          () C { return justify_          ; } // Text justification options. Defaults to center;
      Text & textAnchor       (  TEXT_ANCHOR   value  );   TEXT_ANCHOR   textAnchor       () C { return textAnchor_       ; } // Part of the text placed closest to the anchor. Defaults to center. 
      Text & maxAngle         (  int           degrees);   int           maxAngle         () C { return maxAngle_         ; } // Maximum angle change between adjacent characters. Defaults to 45. PLACEMENT::Line.
      Text & rotate           (  int           degrees);   int           rotate           () C { return rotate_           ; } // Rotates the text clockwise. Defaults to 0.
      Text & padding          (  int           pixels );   int           padding          () C { return padding_          ; } // Size of the additional area around the text bounding box used for detecting symbol collisions. Defaults to 2.
      Text & keepUpright      (  bool          value  );   bool          keepUpright      () C { return keepUpright_      ; } // If true, the text may be flipped vertically to prevent it from being rendered upside - down. Requires rotation alignement 'map' and placement 'line'. Defaults to true.
      Text & transform        (  TRANSFORM     value  );   TRANSFORM     transform        () C { return transform_        ; } // Specifies how to capitalize text, similar to the CSS text-transform property. Defaults to none.
      Text & offset           (C Coordinate  & value  ); C Coordinate  & offset           () C { return offset_           ; } // Offset distance of text from its anchor. Positive values indicate right and down, while negative values indicate left and up.
      Text & allowOverlap     (  bool          value  );   bool          allowOverlap     () C { return allowOverlap_     ; } // If true, the text will be visible even if it collides with other previously drawn symbols. Defaults to false.
      Text & ignorePlacement  (  bool          value  );   bool          ignorePlacement  () C { return ignorePlacement_  ; } // If true, other symbols can be visible even if they collide with the text. Defaults to false.
      
      // Paint properties
      Text & opacity  (  float        value );   float        opacity  () C { return opacity_  ; } // The opacity at which the text will be drawn. Defaults to 1.
      Text & color    (C Wt::WColor & value ); C Wt::WColor & color    () C { return color_    ; } // The color with which the text will be drawn. Defaults to black.
      Text & haloColor(C Wt::WColor & value ); C Wt::WColor & haloColor() C { return haloColor_; } // The color of the text’s halo, which helps it stand out from backgrounds. Defaults to transparent.
      Text & haloWidth(  int          pixels);   int          haloWidth() C { return haloWidth_; } // Distance of halo to the font outline. Max text halo width is 1/4 of the font-size. Defaults to 0.
      Text & haloBlur (  int          pixels);   int          haloBlur () C { return haloBlur_ ; } // The halo’s fadeout distance towards the outside. Defaults to 0.

      Text & translate(C Coordinate & offset, ANCHOR anchor = ANCHOR::Map); // // Distance that the text’s anchor is moved from its original placement. Positive values indicate right and down, while negative values indicate left and up. Anchor controls whether the translation is relative to the map (north) or viewport (screen).
      C Coordinate & translation() C{ return translate_; }
      ANCHOR anchor() C{ return anchor_; }

    private:
      ANCHOR pitchAlignment_, rotationAlignment_, anchor_;
      JUSTIFY justify_;
      TEXT_ANCHOR textAnchor_;
      TRANSFORM transform_;
      Coordinate offset_, translate_;    
      Wt::WString label_, font_;
      Wt::WColor color_, haloColor_;
      float size_, maxWidth_, lineHeight_, spacing_, opacity_;
      int maxAngle_, rotate_, padding_, haloWidth_, haloBlur_;
      bool optional_, keepUpright_, allowOverlap_, ignorePlacement_;
      bool pitchAlignmentSet;
      SymbolLayer * parent;
    };

    Text text;

  private:
    PLACEMENT placement_;
    int spacing_;
    bool avoidEdges_;
    bool optional_;

  };

}