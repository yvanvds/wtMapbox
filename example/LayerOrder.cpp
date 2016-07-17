#include "stdafx.h"
#include "LayerOrder.h"
#include "mapboxApplication.h"

LayerOrder::LayerOrder()
{
  source.set("https://d2ad6b4ur7yvpq.cloudfront.net/naturalearth-3.3.0/ne_50m_urban_areas.geojson");

  layer.set(&source);
  layer.color(Wt::WColor("#f08")).opacity(0.4);

}

void LayerOrder::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->add(&source).add(&layer, "water");
  APP->getMap()->center(MapBox::Coordinate(35.1374518, -88.13734)).zoom(4);
  APP->getMap()->applyMapStyle();
}

void LayerOrder::onHide()
{
  APP->getMap()->rem(&source).rem(&layer);
}
