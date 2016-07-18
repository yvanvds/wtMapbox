#include "ImageSource.h"
#include "Conversions.h"
#include "Map.h"

namespace MapBox {

  ImageSource::ImageSource()
    : Source(SOURCETYPE::Image)
  {}

  ImageSource & ImageSource::coordinates(C Coordinate & topLeft, C Coordinate & topRight, C Coordinate & bottomRight, C Coordinate & bottomLeft)
  {
    this->topLeft = topLeft;
    this->topRight = topRight;
    this->bottomLeft = bottomLeft;
    this->bottomRight = bottomRight;
    return *this;
  }

  Wt::WString ImageSource::render(Map * parent)
  {
    parent_ = parent;

    std::stringstream stream;
    stream
      << "'" << id_ << "', {\n"
      << "  type: 'image',\n"
      << "  url: '" << url_ << "',\n"
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