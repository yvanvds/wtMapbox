#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class MapStyle : public Demo
{
public:
  MapStyle();

  virtual void onShow();
  virtual void onHide();

private:
  Wt::WButtonGroup * group;
};