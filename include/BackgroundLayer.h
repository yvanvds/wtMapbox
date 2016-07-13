#pragma once
#include "Layer.h"

namespace MapBox {

  class BackgroundLayer : public Layer
  {
  public:
    BackgroundLayer();
    
    BackgroundLayer & color  (const Wt::WColor  & value); const Wt::WColor  & color  () const;
    BackgroundLayer & pattern(const std::string & value);       std::string   pattern() const;
    BackgroundLayer & opacity(      int           value);       int           opacity() const;

  private:
    Wt::WColor color_;
  };

} // namespace MapBox

