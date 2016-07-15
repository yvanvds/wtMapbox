#include "stdafx.h"
#include "DisplayMap.h"
#include "mapboxApplication.h"

DisplayMap::DisplayMap()
{

}

void DisplayMap::onShow() {
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE_STREETS);
}
void DisplayMap::onHide() {

}

