#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class InfoPopup : public Demo
{
public:
  InfoPopup();

  virtual void onShow();
  virtual void onHide();

private:

  void createCollection();

  MapBox::GeoJSONSource source;
  MapBox::GFeatureCollection collection;
  MapBox::SymbolLayer layer;
  MapBox::JSHandler click;
  MapBox::JSHandler move;
};