#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class FeatureOnClick : public Demo {
public:
  FeatureOnClick();

  virtual void onShow();
  virtual void onHide();

private:

  MapBox::GeoJSONSource source;
  MapBox::FillLayer layer;
  MapBox::GFeature feature;
  MapBox::Coordinate coordinate;
  boost::signals2::connection connection;

  Wt::WText * text;
  MapBox::Popup * popup;
};