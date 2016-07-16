#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class DisplayPopup : public Demo
{
public:
  DisplayPopup();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::Popup * popup;
};