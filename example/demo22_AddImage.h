#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class AddImage : public Demo {
public:
  AddImage();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::ImageSource source;
  MapBox::RasterLayer layer;
};