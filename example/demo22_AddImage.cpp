#include "demo22_AddImage.h"
#include "stdafx.h"
#include "mapboxApplication.h"

AddImage::AddImage()
{
  source.set("http://127.0.0.1:8080/radar.gif");
  source.coordinates(
    MapBox::Coordinate(46.437, -80.425),
    MapBox::Coordinate(46.437, -71.516),
    MapBox::Coordinate(37.936, -71.516),
    MapBox::Coordinate(37.936, -80.425)
  );

  layer.set(&source);
  layer.opacity(0.85);
}

void AddImage::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Dark, true);
  APP->getMap()->center(MapBox::Coordinate(41.874, -75.789)).zoom(5);
  APP->getMap()->add(&source).add(&layer, "boundaries");
  APP->getMap()->applyMapStyle();
}

void AddImage::onHide()
{
  APP->getMap()->rem(&layer).rem(&source);
}
