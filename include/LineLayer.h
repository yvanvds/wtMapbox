#pragma once
#include "Layer.h"
#include "Enumerations.h"
#include "Coordinate.h"

namespace MapBox {

  class LineLayer : public Layer {
  public:
    LineLayer();

    LineLayer & cap       (CAP   value); CAP   cap       () const;
    LineLayer & join      (JOIN  value); JOIN  join      () const;
    LineLayer & miterLimit(float value); float miterLimit() const;
    LineLayer & roundLimit(float value); float roundLimit() const;

    LineLayer & opacity  (float value); float opacity  () const;
    LineLayer & width    (int   value); int   width    () const;
    LineLayer & gapWidth (int   value); int   gapWidth () const;
    LineLayer & offset   (int   value); int   offset   () const;
    LineLayer & blur     (int   value); int   blur     () const;
    LineLayer & dashArray(float value); float dashArray() const;

    LineLayer & pattern  (const std::string & value);       std::string   pattern() const;
    LineLayer & color    (const Wt::WColor  & value); const Wt::WColor  & color  () const;

    LineLayer & translate(const Coordinate & offset, ANCHOR anchor = ANCHOR::Map);
    const Coordinate & translation() const { return translate_; }
    ANCHOR anchor() const { return anchor_; }

  private:
    CAP        cap_      ;
    JOIN       join_     ;
    Wt::WColor color_    ;
    Coordinate translate_;
    ANCHOR     anchor_   ;
  };

}