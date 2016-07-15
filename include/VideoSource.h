#pragma once
#include "Source.h"
#include "Coordinate.h"

namespace MapBox {

  class VideoSource : public Source {
  public:
    VideoSource();

    virtual Source & setFromURL(C Wt::WString & url); // Inherited from Source. Video uses more sources and you should use the addURL method instead.
    VideoSource & addUrl(C Wt::WString & url);
    VideoSource & coordinates(C Coordinate & topLeft, C Coordinate & topRight, C Coordinate & bottomRight, C Coordinate & bottomLeft);

    virtual Wt::WString render();

  private:
    Coordinate topLeft, topRight, bottomRight, bottomLeft;
    std::vector<Wt::WString> urls;
  };

}
