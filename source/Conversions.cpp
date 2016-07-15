#include "Conversions.h"


namespace MapBox {

  Wt::WString ToScript(bool value) {
    if (value) return "true";
    return "false";
  }

  Wt::WString ToScript(int value) {
    return std::to_string(value);
  }

  Wt::WString ToScript(float value) {
    return std::to_string(value);
  }

  Wt::WString ToScript(ANCHOR value)
  {
    if (value == ANCHOR::Map) return "map";
    return "viewport";
  }

  Wt::WString ToScript(CAP value) {
    switch (value) {
    case CAP::Butt: return "'butt'";
    case CAP::Round: return "'round'";
    case CAP::Square: return "'square'";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(JOIN value) {
    switch (value) {
    case JOIN::Bevel: return "'bevel'";
    case JOIN::Round: return "'round'";
    case JOIN::Miter: return "'miter'";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(PLACEMENT value)
  {
    switch (value) {
    case PLACEMENT::Line: return "line";
    case PLACEMENT::Point: return "point";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(JUSTIFY value)
  {
    switch (value) {
    case JUSTIFY::Center: return "center";
    case JUSTIFY::Left: return "left";
    case JUSTIFY::Right: return "right";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(TEXT_ANCHOR value)
  {
    switch (value) {
    case TEXT_ANCHOR::Bottom: return "bottom";
    case TEXT_ANCHOR::BottomLeft: return "bottom-left";
    case TEXT_ANCHOR::BottomRight: return "bottom-right";
    case TEXT_ANCHOR::Center: return "center";
    case TEXT_ANCHOR::Left: return "left";
    case TEXT_ANCHOR::Right: return "right";
    case TEXT_ANCHOR::Top: return "top";
    case TEXT_ANCHOR::TopLeft: return "top-left";
    case TEXT_ANCHOR::TopRight: return "top-right";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(TRANSFORM value)
  {
    switch (value) {
    case TRANSFORM::None: return "none";
    case TRANSFORM::lowercase: return "lowercase";
    case TRANSFORM::UPPERCASE: return "uppercase";
    }
    return Wt::WString();
  }

  Wt::WString ToScript(C Coordinate & value) {
    return "[" + std::to_string(value.longitude()) + ", " + std::to_string(value.latitude()) + "]";
  }

  Wt::WString ToScript(C Wt::WColor & value) {
    return "'" + value.cssText() + "'";
  }

}