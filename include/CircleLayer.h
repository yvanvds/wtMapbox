#pragma once
#include "Layer.h"
#include "Coordinate.h"
#include "Enumerations.h"

namespace MapBox {


  class CircleLayer : public Layer
  {
  public:
    CircleLayer();

    
    
    // paint properties
    CircleLayer & radius (      int          value);       int          radius () const;
    CircleLayer & color  (const Wt::WColor & value); const Wt::WColor & color  () const;
    CircleLayer & blur   (      float        value);       float        blur   () const;
    CircleLayer & opacity(      float        value);       float        opacity() const;

    CircleLayer & translate(const Coordinate & offset, ANCHOR anchor = ANCHOR::Map);
    const Coordinate & translation() const { return translate_; }
    ANCHOR anchor() const { return anchor_; }

  private:

    // properties to remember for easy retrieval
    Wt::WColor color_    ;
    Coordinate translate_;
    ANCHOR     anchor_   ;

  };

} // namespace MapBox

