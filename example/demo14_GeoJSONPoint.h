#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class GeoJSONPoint : public Demo {
public:
  GeoJSONPoint();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GFeatureCollection featureCollection;
  MapBox::GeoJSONSource source;
  MapBox::SymbolLayer layer;
};