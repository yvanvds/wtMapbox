#include "stdafx.h"
#include "RasterTiles.h"
#include "mapboxApplication.h"

RasterTiles::RasterTiles()
{
  source.setFromURL("mapbox://mapbox.streets");
  source.tileSize(256);

  layer.setSource(&source);
  layer.setZoom(0, 22);
}

void RasterTiles::onShow()
{
  APP->getMap()->addSource(&source);
  APP->getMap()->addLayer(&layer);
  APP->getMap()->setCenter(MapBox::Coordinate(40, -74.5));
  APP->getMap()->setZoom(2);
}

void RasterTiles::onHide()
{
  APP->getMap()->removeSource(&source);
  APP->getMap()->removeLayer(&layer);
}

