#include "Conversions.h"


namespace MapBox {

  std::string ToScript(bool value) {
    if (value) return "true";
    return "false";
  }

  std::string ToScript(int value) {
    return std::to_string(value);
  }

  std::string ToScript(float value) {
    return std::to_string(value);
  }

  std::string ToScript(ANCHOR value)
  {
    if (value == ANCHOR::Map) return "map";
    return "viewport";
  }

  std::string ToScript(CAP value) {
    switch (value) {
    case CAP::Butt: return "butt";
    case CAP::Round: return "round";
    case CAP::Square: return "square";
    }
    return std::string();
  }

  std::string ToScript(JOIN value) {
    switch (value) {
    case JOIN::Bevel: return "bevel";
    case JOIN::Round: return "round";
    case JOIN::Miter: return "miter";
    }
    return std::string();
  }

  std::string ToScript(PLACEMENT value)
  {
    switch (value) {
    case PLACEMENT::Line: return "line";
    case PLACEMENT::Point: return "point";
    }
    return std::string();
  }

  std::string ToScript(JUSTIFY value)
  {
    switch (value) {
    case JUSTIFY::Center: return "center";
    case JUSTIFY::Left: return "left";
    case JUSTIFY::Right: return "right";
    }
    return std::string();
  }

  std::string ToScript(TEXT_ANCHOR value)
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
    return std::string();
  }

  std::string ToScript(TRANSFORM value)
  {
    switch (value) {
    case TRANSFORM::None: return "none";
    case TRANSFORM::lowercase: return "lowercase";
    case TRANSFORM::UPPERCASE: return "uppercase";
    }
    return std::string();
  }

  std::string ToScript(C Coordinate & value) {
    return "[" + std::to_string(value.latitude()) + ", " + std::to_string(value.longitude()) + "]";
  }

  std::string ToScript(C Wt::WColor & value) {
    return "'" + value.cssText() + "'";
  }

}