#pragma once
#include "Source.h"
#include "Definitions.h"

namespace MapBox {

  class RasterSource : public Source {
  public:
    RasterSource();

    RasterSource & tileSize(int value); int tileSize() C { return tileSize_; }

    virtual std::string render();

  private:
    int tileSize_;
  };

}