#include "demo23_AddVideo.h"
#include "stdafx.h"
#include "mapboxApplication.h"

AddVideo::AddVideo()
{
  source.add("http://127.0.0.1:8080/drone.mp4");
  source.add("http://127.0.0.1:8080/drone.webm");
  source.coordinates(
    MapBox::Coordinate(37.5623881, -122.515963),
    MapBox::Coordinate(37.5641018, -122.514676),
    MapBox::Coordinate(37.5633917, -122.513093),
    MapBox::Coordinate(37.5616184, -122.514231)
  );

  layer.set(&source);
}

void AddVideo::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Satellite, true);
  APP->getMap()->center(MapBox::Coordinate(37.562984, -122.514426)).zoom(17).bearing(-96);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->applyMapStyle();
}

void AddVideo::onHide()
{
  APP->getMap()->rem(&layer).rem(&source).bearing(0);
}
