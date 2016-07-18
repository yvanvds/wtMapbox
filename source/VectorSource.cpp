#include "VectorSource.h"
#include "Map.h"

MapBox::VectorSource::VectorSource()
  : Source(SOURCETYPE::Vector)
{

}

Wt::WString MapBox::VectorSource::render(Map * parent)
{
  parent_ = parent;

  std::stringstream stream;
  stream
    << "'" << id_ << "', {\n"
    << "  type: 'vector',\n"
    << "  url: '" << url_ << "'\n"
    << "}\n";
  return stream.str();
}
