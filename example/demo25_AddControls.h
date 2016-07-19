#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class AddControls : public Demo
{
public:
  AddControls();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::Control * navigation;
  MapBox::Control * geoLocate;
  MapBox::Control * geoCoder;
  MapBox::Control * directions;
};