#include "stdafx.h"
#include "demo01_DisplayMap.h"
#include "mapboxApplication.h"

DisplayMap::DisplayMap()
{

}

void DisplayMap::onShow() {
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets);
}
void DisplayMap::onHide() {

}

