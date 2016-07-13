#include "Enumerations.h"

namespace MapBox {

  std::string AnchorToString(ANCHOR value)
  {
    if (value == ANCHOR::Map) return "map";
    return "viewport";
  }

  std::string CapToString(CAP value) {
    switch (value) {
      case CAP::Butt  : return "Butt"  ;
      case CAP::Round : return "Round" ;
      case CAP::Square: return "Square";
    }
  }

  std::string JoinToString(JOIN value) {
    switch (value) {
      case JOIN::Bevel: return "Bevel";
      case JOIN::Round: return "Round";
      case JOIN::Miter: return "Miter";
    }
  }

}