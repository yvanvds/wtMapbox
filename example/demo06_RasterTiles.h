#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class RasterTiles : public Demo
{
public:
  RasterTiles();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::RasterSource source;
  MapBox::RasterLayer layer;
};