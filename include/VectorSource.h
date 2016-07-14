#pragma once
#include "Source.h"

namespace MapBox {

  class VectorSource : public Source {
  public:
    VectorSource();

    virtual std::string render();

  };

}