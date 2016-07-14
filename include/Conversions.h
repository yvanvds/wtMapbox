#pragma once

#include "Enumerations.h"
#include "Coordinate.h"
#include "Definitions.h"

namespace MapBox {
  // helper functions to get values to javascript

  // basic types
  std::string ToScript(bool value);
  std::string ToScript(int value);
  std::string ToScript(float value);

  // enums
  std::string ToScript(ANCHOR value);
  std::string ToScript(CAP value);
  std::string ToScript(JOIN value);
  std::string ToScript(PLACEMENT value);
  std::string ToScript(JUSTIFY value);
  std::string ToScript(TEXT_ANCHOR value);
  std::string ToScript(TRANSFORM value);

  // classes
  std::string ToScript(C Coordinate & value);
  std::string ToScript(C Wt::WColor & value);

}