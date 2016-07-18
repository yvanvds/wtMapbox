#pragma once

#include <string>
#include <vector>
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {
  class Coordinate;
  class Map;

  class Source
  {
  public:
    Source(SOURCETYPE type);
    
      SOURCETYPE    type() { return type_; }
    C Wt::WString & id  () { return id_  ; }
    
    virtual Source & set(C Wt::WString & url);

    virtual Wt::WString render(Map * parent) = 0;

  protected:
    SOURCETYPE type_;
    Wt::WString id_;
    Wt::WString url_;

    Map * parent_;
  };

} // namespace MapBox
