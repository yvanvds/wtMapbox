#pragma once
#include "wtMapbox.h"
#include "Demo.h"


using namespace Wt;

class DataDrivenColors : public Demo
{
public:
  DataDrivenColors();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::VectorSource source;
  MapBox::CircleLayer layer;
};

