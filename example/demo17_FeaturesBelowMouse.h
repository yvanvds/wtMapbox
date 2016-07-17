#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class FeaturesBelowMouse : public Demo
{
public:
  FeaturesBelowMouse();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::JSHandler mouseMove;
};
