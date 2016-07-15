#pragma once
#include "wtMapbox.h"
#include "Demo.h"

using namespace Wt;

class CreateClusters : public Demo
{
public:
  CreateClusters();

  virtual void onShow();
  virtual void onHide();

private:
  MapBox::GeoJSONSource source;
  MapBox::SymbolLayer unclusteredLayer;
  MapBox::CircleLayer clusterLayer[3];
  MapBox::SymbolLayer clusterCountLayer;

  Wt::WCheckBox * unclusteredCheck;
  Wt::WCheckBox * clusterCheck[3];
  Wt::WCheckBox * clusterCountCheck;
};

