#include "demo13_GeoJSONPoly.h"
#include "stdafx.h"
#include "mapboxApplication.h"

GeoJSONPoly::GeoJSONPoly()
{
  poly.add(MapBox::Coordinate(45.1374518, -67.137343))
    .add(MapBox::Coordinate(44.8097, -66.96466))
    .add(MapBox::Coordinate(44.3252, -68.03252))
    .add(MapBox::Coordinate(43.98, -69.06))
    .add(MapBox::Coordinate(43.68405, -70.11617))
    .add(MapBox::Coordinate(43.09008331, -70.6457340))
    .add(MapBox::Coordinate(43.08003225, -70.751024))
    .add(MapBox::Coordinate(43.21973948, -70.797611))
    .add(MapBox::Coordinate(43.3678958, -70.98176))
    .add(MapBox::Coordinate(43.4663394, -70.944165))
    .add(MapBox::Coordinate(45.30524, -71.08482))
    .add(MapBox::Coordinate(45.460222886, -70.6600225))
    .add(MapBox::Coordinate(45.91479462, -70.3049537))
    .add(MapBox::Coordinate(46.693170884, -70.0001403))
    .add(MapBox::Coordinate(47.447775987, -69.2370861))
    .add(MapBox::Coordinate(47.184794623, -68.9047808))
    .add(MapBox::Coordinate(47.3546292181, -68.2343049))
    .add(MapBox::Coordinate(47.066248887, -67.79035274))
    .add(MapBox::Coordinate(45.7025853541, -67.79141211))
    .add(MapBox::Coordinate(45.13745189, -67.13734351));
  Wt::Json::Object properties;
  properties["name"] = Wt::WString("Maine");

  feature.geometry(poly);
  feature.properties(properties);

  source.set(&feature);

  layer.set(&source);
  layer.color(Wt::WColor("#088"));
  layer.opacity(0.8);
  layer.sourceLayer("Maine");
}

void GeoJSONPoly::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(MapBox::Coordinate(45.1374518906, -68.13734351)).zoom(5);
  APP->getMap()->applyMapStyle();
}

void GeoJSONPoly::onHide()
{
  APP->getMap()->rem(&layer).rem(&source);
}
