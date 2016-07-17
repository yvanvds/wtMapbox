#include "stdafx.h"
#include "demo06_RasterTiles.h"
#include "mapboxApplication.h"

RasterTiles::RasterTiles()
{
  source.set("mapbox://mapbox.streets");
  source.tileSize(256);

  layer.set(&source);
  layer.zoom(0, 22);
}

void RasterTiles::onShow()
{
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(MapBox::Coordinate(40, -74.5)).zoom(2);
}

void RasterTiles::onHide()
{
  APP->getMap()->rem(&source).rem(&layer);
}

