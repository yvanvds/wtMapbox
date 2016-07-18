#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class RealtimeData : public Demo {
public:
  RealtimeData();

  virtual void onShow();
  virtual void onHide();

private:

  void timeout();

  MapBox::GeoJSONSource source;
  MapBox::SymbolLayer layer;

  Wt::WTimer * timer;
};