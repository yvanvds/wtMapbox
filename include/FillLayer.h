#pragma once
#include "Layer.h"
#include "Enumerations.h"
#include "Coordinate.h";

namespace MapBox {

  class FillLayer : public Layer
  {
  public:
    FillLayer();
    
    FillLayer & antialias   (      bool         value);       bool         antialias   () const;
    FillLayer & opacity     (      float        value);       float        opacity     () const;
    FillLayer & color       (const Wt::WColor & value); const Wt::WColor & color       () const;
    FillLayer & outlineColor(const Wt::WColor & value); const Wt::WColor & outlineColor() const;
    
    FillLayer & translate(const Coordinate & offset, ANCHOR anchor = ANCHOR::Map);
    const Coordinate & translation() const { return translate_; }
    ANCHOR anchor() const { return anchor_; }

  private:
    Wt::WColor color_       ;
    Wt::WColor outlineColor_;
    Coordinate translate_   ;
    ANCHOR     anchor_      ;
  };

}

