#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class AddVideo : public Demo {
public:
  AddVideo();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::VideoSource source;
  MapBox::RasterLayer layer;
};