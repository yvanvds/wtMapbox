#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class GeoJSONLine : public Demo {
public:
  GeoJSONLine();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GLineString line;
  MapBox::GeoJSONSource source;
  MapBox::LineLayer layer;
};