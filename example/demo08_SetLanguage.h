#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class SetLanguage : public Demo {
public:
  SetLanguage();

  virtual void onShow();
  virtual void onHide();

private:
  Wt::WButtonGroup * group;
};