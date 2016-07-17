#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class GeoJSONPoly : public Demo {
public:
  GeoJSONPoly();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GPolygon poly;
  MapBox::GFeature feature;
  MapBox::GeoJSONSource source;
  MapBox::FillLayer layer;
};