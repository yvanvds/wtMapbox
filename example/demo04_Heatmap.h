#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class Heatmap : public Demo {
public:
  Heatmap();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GeoJSONSource source;
  MapBox::CircleLayer layer[4];

};