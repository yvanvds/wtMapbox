#pragma once
#include "wtMapbox.h"
#include "Demo.h"

class AddImage : public Demo {
public:
  AddImage();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::VectorSource mapbox;
  MapBox::ImageSource overlay;
  MapBox::BackgroundLayer background;
  MapBox::FillLayer water;
  MapBox::LineLayer boundaries;
  MapBox::RasterLayer overlayer;
  MapBox::SymbolLayer cities;
  MapBox::SymbolLayer states;
};