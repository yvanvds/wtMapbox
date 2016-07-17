#pragma once

#include "wtMapbox.h"
#include "Demo.h"

class GetCoordinates : public Demo {
public:
  GetCoordinates();

  virtual void onShow();
  virtual void onHide();

private:
  Wt::WText * coord;
  Wt::Signals::connection connection;
};