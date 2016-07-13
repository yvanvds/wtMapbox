#pragma once
#include "wtMapbox.h"

using namespace Wt;

class MenuBar : public WContainerWidget
{
public:
  MenuBar(WContainerWidget * parent = 0);

private:
  void createDemo1();
  WPanel * demo1;

  void createDemo2();
  WPanel * demo2;

  void createDemo3();
  WPanel * demo3;
  WCheckBox * heatmap;


  MapBox::GeoJSONSource demo3Source;
  MapBox::CircleLayer demo3Layer1;
  MapBox::CircleLayer demo3Layer2;
  MapBox::CircleLayer demo3Layer3;
  MapBox::CircleLayer demo3Layer4;
};

