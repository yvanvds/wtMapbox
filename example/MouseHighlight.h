#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class MouseHighlight : public Demo {
public:
  MouseHighlight();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GeoJSONSource source;
  MapBox::FillLayer fills;
  MapBox::LineLayer borders;
  MapBox::FillLayer hover;

  Wt::WString mouseMoveFunction;
  Wt::WString mouseOutFunction;
};