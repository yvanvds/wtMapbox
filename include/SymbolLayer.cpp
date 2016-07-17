#include "SymbolLayer.h"
#include "Conversions.h"

namespace MapBox {
  SymbolLayer::SymbolLayer() 
    : icon(this)
    , text(this)
  {
    type(LAYERTYPE::Symbol);
    placement_  = PLACEMENT::Point;
    spacing_    = 250;
    avoidEdges_ = false;
    optional_   = false;
  }

  SymbolLayer & SymbolLayer::placement(PLACEMENT value)
  {
    placement_ = value;
    setLayout("symbol-placement", ToScript(value));
    return *this;
  }

  SymbolLayer & SymbolLayer::spacing(int pixels)
  {
    spacing_ = pixels;
    setLayout("symbol-spacing", ToScript(pixels));
    return *this;
  }

  SymbolLayer & SymbolLayer::avoidEdges(bool value)
  {
    avoidEdges_ = value;
    setLayout("symbol-avoid-edges", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon::Icon(SymbolLayer * parent)
    : parent(parent)
  {
    allowOverlap_      = false;
    ignorePlacement_   = false;
    optional_          = false;
    rotationAlignment_ = ANCHOR::Viewport;
    size_              = 1;
    rotate_            = 0;
    padding_           = 2;
    keepUpright_       = false;
    offset_            = Coordinate(0, 0);
    opacity_           = 1;
    color_             = Wt::WColor(0, 0, 0);
    haloColor_         = Wt::WColor(0, 0, 0, 0);
    haloWidth_         = 0;
    haloBlur_          = 0;
    translate_         = Coordinate(0, 0);
    anchor_            = ANCHOR::Map;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::allowOverlap(bool value)
  {
    allowOverlap_ = value;
    parent->setLayout("icon-allow-overlap", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::ignorePlacement(bool value)
  {
    ignorePlacement_ = value;
    parent->setLayout("icon-ignore-placement", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::optional(bool value) {
    optional_ = value;
    parent->setLayout("icon-optional", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::rotationAlignment(ANCHOR value) {
    rotationAlignment_ = value;
    parent->setLayout("icon-rotation-alignment", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::size(float value) {
    size_ = value;
    parent->setLayout("icon-size", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::image(C Wt::WString & value) {
    image_ = value;
    parent->setLayout("icon-image", Quote(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::rotate(int degrees) {
    rotate_ = degrees;
    parent->setLayout("icon-rotate", ToScript(degrees));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::padding(int pixels) {
    padding_ = pixels;
    parent->setLayout("icon-padding", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::keepUpright(bool value) {
    keepUpright_ = value;
    parent->setLayout("icon-keep-upright", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::offset(C Coordinate & value) {
    offset_ = value;
    parent->setLayout("icon-offset", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::opacity(float value) {
    opacity_ = value;
    parent->setPaint("icon-opacity", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::color(C Wt::WColor & value) {
    color_ = value;
    parent->setPaint("icon-color", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::haloColor(C Wt::WColor & value) {
    haloColor_ = value;
    parent->setPaint("icon-halo-color", ToScript(value));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::haloWidth(int pixels) {
    haloWidth_ = pixels;
    parent->setPaint("icon-halo-width", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::haloBlur(int pixels) {
    haloBlur_ = pixels;
    parent->setPaint("icon-halo-blur", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Icon & SymbolLayer::Icon::translate(const Coordinate & offset, ANCHOR anchor) {
    parent->setPaint("icon-translate", ToScript(offset));
    parent->setPaint("icon-translate-anchor", ToScript(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }

  SymbolLayer::Text::Text(SymbolLayer * parent)
    : parent(parent)
  {
    pitchAlignment_    = ANCHOR::Viewport;
    rotationAlignment_ = ANCHOR::Viewport;
    font_              = "[Open Sans Regular, Arial Unicode MS Regular]";
    size_              = 16;
    maxWidth_          = 10;
    lineHeight_        = 1.2f;
    spacing_           = 0;
    justify_           = JUSTIFY::Center;
    textAnchor_        = TEXT_ANCHOR::Center;
    maxAngle_          = 45;
    rotate_            = 0;
    padding_           = 2;
    keepUpright_       = true;
    transform_         = TRANSFORM::None;
    offset_            = Coordinate(0, 0);
    allowOverlap_      = false;
    ignorePlacement_   = false;
    optional_          = false;
    opacity_           = 1;
    color_             = Wt::WColor(0, 0, 0);
    haloColor_         = Wt::WColor(0, 0, 0, 0);
    haloWidth_         = 0;
    haloBlur_          = 0;
    translate_         = Coordinate(0, 0);
    anchor_            = ANCHOR::Map;

    pitchAlignmentSet = false;
  }

  SymbolLayer::Text & SymbolLayer::Text::pitchAlignment(ANCHOR value) {
    pitchAlignmentSet = true;
    pitchAlignment_ = value;
    parent->setLayout("text-pitch-alignment", ToScript(value));
    return *this;
  }

  ANCHOR SymbolLayer::Text::pitchAlignment() C {
    if (!pitchAlignmentSet) {
      return rotationAlignment_;
    } 
    return pitchAlignment_;
  }

  SymbolLayer::Text & SymbolLayer::Text::rotationAlignment(ANCHOR value) {
    pitchAlignment_ = value;
    parent->setLayout("text-rotation-alignment", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::label(C Wt::WString & value) {
    label_ = value;
    parent->setLayout("text-field", Quote(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::font(C Wt::WString & value) {
    font_ = value;
    parent->setLayout("text-font", value);
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::size(float pixels) {
    size_ = pixels;
    parent->setLayout("text-size", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::optional(bool value) {
    optional_ = value;
    parent->setLayout("text-optional", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::maxWidth(float em) {
    maxWidth_ = em;
    parent->setLayout("text-max-width", ToScript(em));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::lineHeight(float em) {
    lineHeight_ = em;
    parent->setLayout("text-line-height", ToScript(em));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::spacing(float em) {
    spacing_ = em;
    parent->setLayout("text-letter-spacing", ToScript(em));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::justify(JUSTIFY value) {
    justify_ = value;
    parent->setLayout("text-justify", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::textAnchor(TEXT_ANCHOR value) {
    textAnchor_ = value;
    parent->setLayout("text-anchor", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::maxAngle(int degrees) {
    maxAngle_ = degrees;
    parent->setLayout("text-max-angle", ToScript(degrees));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::rotate(int degrees) {
    rotate_ = degrees;
    parent->setLayout("text-rotate", ToScript(degrees));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::padding(int pixels) {
    padding_ = pixels;
    parent->setLayout("text-padding", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::keepUpright(bool value) {
    keepUpright_ = value;
    parent->setLayout("text-keep-upright", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::transform(TRANSFORM value) {
    transform_ = value;
    parent->setLayout("text-transform", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::offset(C Coordinate & value) {
    offset_ = value;
    parent->setLayout("text-offset", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::allowOverlap(bool value) {
    allowOverlap_ = value;
    parent->setLayout("text-allow-overlap", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::ignorePlacement(bool value) {
    ignorePlacement_ = value;
    parent->setLayout("text-ignore-placement", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::opacity(float value) {
    opacity_ = value;
    parent->setPaint("text-opacity", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::color(C Wt::WColor & value) {
    color_ = value;
    parent->setPaint("text-color", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::haloColor(C Wt::WColor & value) {
    haloColor_ = value;
    parent->setPaint("text-halo-color", ToScript(value));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::haloWidth(int pixels) {
    haloWidth_ = pixels;
    parent->setPaint("text-halo-width", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::haloBlur(int pixels) {
    haloBlur_ = pixels;
    parent->setPaint("text-halo-blur", ToScript(pixels));
    return *this;
  }

  SymbolLayer::Text & SymbolLayer::Text::translate(const Coordinate & offset, ANCHOR anchor) {
    parent->setPaint("text-translate", ToScript(offset));
    parent->setPaint("text-translate-anchor", ToScript(anchor));
    translate_ = offset;
    anchor_ = anchor;
    return *this;
  }
}


