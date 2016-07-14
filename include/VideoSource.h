#pragma once
#include "Source.h"
#include "Coordinate.h"

namespace MapBox {

  class VideoSource : public Source {
  public:
    VideoSource();

    virtual Source & setFromURL(C std::string & url); // Inherited from Source. Video uses more sources and you should use the addURL method instead.
    VideoSource & addUrl(C std::string & url);
    VideoSource & coordinates(C Coordinate & topLeft, C Coordinate & topRight, C Coordinate & bottomRight, C Coordinate & bottomLeft);

    virtual std::string render();

  private:
    Coordinate topLeft, topRight, bottomRight, bottomLeft;
    std::vector<std::string> urls;
  };

}
