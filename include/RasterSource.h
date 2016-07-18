#pragma once
#include "Source.h"
#include "Definitions.h"

namespace MapBox {

  class RasterSource : public Source {
  public:
    RasterSource();

    RasterSource & tileSize(int value); int tileSize() C { return tileSize_; }

    virtual Wt::WString render(Map * parent);

  private:
    int tileSize_;
  };

}