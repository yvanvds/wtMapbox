#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class LayerOrder : public Demo {
public:
  LayerOrder();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GeoJSONSource source;
  MapBox::FillLayer layer;
};