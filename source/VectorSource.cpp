#include "VectorSource.h"

MapBox::VectorSource::VectorSource()
  : Source(SOURCETYPE::Vector)
{

}

Wt::WString MapBox::VectorSource::render()
{
  std::stringstream stream;
  stream
    << "'" << id_ << "', {\n"
    << "  type: 'vector',\n"
    << "  url: '" << url_ << "'\n"
    << "}\n";
  return stream.str();
}
