#pragma once

#include <string>
#include <vector>
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {
  class Coordinate;

  class Source
  {
  public:
    Source(SOURCETYPE type);
    
      SOURCETYPE    type() { return type_; }
    C std::string & id  () { return id_  ; }
    
    virtual Source & setFromURL(C std::string & url);

    virtual std::string render() = 0;

  protected:
    SOURCETYPE type_;
    std::string id_;
    std::string url_;

  };

} // namespace MapBox
