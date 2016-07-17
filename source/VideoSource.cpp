#include "VideoSource.h"
#include "Enumerations.h"
#include "Conversions.h"

namespace MapBox {



  VideoSource::VideoSource()
    : Source(SOURCETYPE::Video)
  {
  }

  Source & VideoSource::set(C Wt::WString & url)
  {
    add(url);
    return *this;
  }

  VideoSource & VideoSource::add(C Wt::WString & url)
  {
    urls.emplace_back(url);
    return *this;
  }

  VideoSource & VideoSource::coordinates(C Coordinate & topLeft, C Coordinate & topRight, C Coordinate & bottomRight, C Coordinate & bottomLeft)
  {
    this->topLeft = topLeft;
    this->topRight = topRight;
    this->bottomLeft = bottomLeft;
    this->bottomRight = bottomRight;
    return *this;
  }

  Wt::WString VideoSource::render()
  {
    std::stringstream stream;
    stream
      << "'" << id_ << "', {\n"
      << "  type: 'video',\n"
      << "  urls: [\n";

    for (int i = 0; i < urls.size(); i++) {
      stream << "    '" << urls[i] << "'";
      if (i < (urls.size() - 1)) stream << ", \n";
      else {
        stream << "\n";
        stream << "  ],\n";
      }
    }

    stream  
      << "  coordinates: [\n"
      << "    " << ToScript(topLeft) << ",\n"
      << "    " << ToScript(topRight) << ",\n"
      << "    " << ToScript(bottomRight) << ",\n"
      << "    " << ToScript(bottomLeft) << "\n"
      << "  ]\n"
      << "}\n";
    return stream.str();
  }

}