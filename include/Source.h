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
    C Wt::WString & id  () { return id_  ; }
    
    virtual Source & setFromURL(C Wt::WString & url);

    virtual Wt::WString render() = 0;

  protected:
    SOURCETYPE type_;
    Wt::WString id_;
    Wt::WString url_;

  };

} // namespace MapBox
