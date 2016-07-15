#pragma once

#include "Enumerations.h"
#include "Coordinate.h"
#include "Definitions.h"

namespace MapBox {
  // helper functions to get values to javascript

  // basic types
  Wt::WString ToScript(bool value);
  Wt::WString ToScript(int value);
  Wt::WString ToScript(float value);

  // enums
  Wt::WString ToScript(ANCHOR value);
  Wt::WString ToScript(CAP value);
  Wt::WString ToScript(JOIN value);
  Wt::WString ToScript(PLACEMENT value);
  Wt::WString ToScript(JUSTIFY value);
  Wt::WString ToScript(TEXT_ANCHOR value);
  Wt::WString ToScript(TRANSFORM value);

  // classes
  Wt::WString ToScript(C Coordinate & value);
  Wt::WString ToScript(C Wt::WColor & value);

}