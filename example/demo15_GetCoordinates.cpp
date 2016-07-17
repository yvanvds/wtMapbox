#include "stdafx.h"
#include "demo15_GetCoordinates.h"
#include "mapboxApplication.h"

GetCoordinates::GetCoordinates()
{
  new Wt::WText("Click on the map to retrieve the coordinate.", this);
  new Wt::WBreak(this);

  coord = new Wt::WText(this);
  
}

void GetCoordinates::onShow()
{
  connection = APP->getMap()->clicked().connect(std::bind([=](const MapBox::Coordinate & pos) {
    coord->setText("Long: " + std::to_string(pos.longitude()) + " Lat: " + std::to_string(pos.latitude()));
  }, std::placeholders::_1));
}

void GetCoordinates::onHide()
{
  APP->getMap()->clicked().disconnect(connection);
}
