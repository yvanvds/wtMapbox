#include "GeoJSONLine.h"
#include "stdafx.h"
#include "mapboxApplication.h"

GeoJSONLine::GeoJSONLine()
{
  line.add(MapBox::Coordinate(37.83381888, -122.48369))
    .add(MapBox::Coordinate(37.833174891, -122.4834823))
    .add(MapBox::Coordinate(37.832700366, -122.4833965))
    .add(MapBox::Coordinate(37.832056363, -122.4835681))
    .add(MapBox::Coordinate(37.831141191, -122.4840402))
    .add(MapBox::Coordinate(37.830497174, -122.4840402))
    .add(MapBox::Coordinate(37.829920943, -122.4834823))
    .add(MapBox::Coordinate(37.829548086, -122.4835681))
    .add(MapBox::Coordinate(37.829446397, -122.4850702))
    .add(MapBox::Coordinate(37.828802366, -122.4861001))
    .add(MapBox::Coordinate(37.829310812, -122.4869585))
    .add(MapBox::Coordinate(37.830802235, -122.4870014))
    .add(MapBox::Coordinate(37.831683516, -122.4875164))
    .add(MapBox::Coordinate(37.832158048, -122.4880313))
    .add(MapBox::Coordinate(37.832971523, -122.4888896))
    .add(MapBox::Coordinate(37.832632576, -122.4898767))
    .add(MapBox::Coordinate(37.832937629, -122.4904346))
    .add(MapBox::Coordinate(37.832429207, -122.4912500))
    .add(MapBox::Coordinate(37.832564787, -122.4916362))
    .add(MapBox::Coordinate(37.833378258, -122.4922370))
    .add(MapBox::Coordinate(37.833683307, -122.4937820));

  source.set(&line);
  layer.set(&source);
  layer.join(MapBox::JOIN::Round);
  layer.cap(MapBox::CAP::Round);
  layer.color(Wt::WColor("#888"));
  layer.width(8);
}

void GeoJSONLine::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(MapBox::Coordinate(37.830348, -122.486052)).zoom(15);
  APP->getMap()->applyMapStyle();

}

void GeoJSONLine::onHide()
{
  APP->getMap()->rem(&layer).rem(&source);
}
