#pragma once
#include "Source.h"
#include "Coordinate.h"


namespace MapBox {

  class ImageSource : public Source {
  public:
    ImageSource();

    ImageSource & coordinates(C Coordinate & topLeft, C Coordinate & topRight, C Coordinate & bottomRight, C Coordinate & bottomLeft);

    virtual Wt::WString render(Map * parent);

  private:
    Coordinate topLeft, topRight, bottomRight, bottomLeft;
  };

}