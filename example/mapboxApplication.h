#pragma once
#include "wtMapbox.h"
#include "MenuBar.h"

using namespace Wt;

class mapboxApplication : public WApplication
{
public:
  mapboxApplication(const WEnvironment & env);

  MapBox::Map * getMap() { return map; }

private:

  MenuBar * menuBar;
  MapBox::Map * map;

};

