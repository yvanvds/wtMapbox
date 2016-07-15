#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class HeightLines : public Demo
{
public:
  HeightLines();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::VectorSource museums;
  MapBox::VectorSource contours;
  MapBox::CircleLayer museumLayer;
  MapBox::LineLayer contourLayer;
};