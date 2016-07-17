#include "GeoJSONPoint.h"
#include "stdafx.h"
#include "mapboxApplication.h"

using namespace MapBox;

GeoJSONPoint::GeoJSONPoint()
{
  GPoint point;
  point.set(38.91318805974, -77.03238901);
  Wt::Json::Object properties;
  properties["title"] = Wt::WString("Mapbox DC");
  properties["icon"] = Wt::WString("monument");

  GFeature feature1;
  feature1.geometry(point);
  feature1.properties(properties);

  point.set(37.776, -122.414);
  properties["title"] = Wt::WString("Mapbox SF");
  properties["icon"] = Wt::WString("harbor");

  GFeature feature2;
  feature2.geometry(point);
  feature2.properties(properties);

  featureCollection.add(feature1);
  featureCollection.add(feature2);

  source.set(&featureCollection);

  layer.set(&source);
  layer.icon.image("{icon}-15").size(2);
  layer.text.label("{title}")
            .font("['Open Sans Semibold', 'Arial Unicode MS Bold']")
            .offset(Coordinate(1.6, 0))
            .textAnchor(TEXT_ANCHOR::Top);


}

void GeoJSONPoint::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Light, true);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(MapBox::Coordinate(37.8, -96)).zoom(3);
  APP->getMap()->applyMapStyle();
}

void GeoJSONPoint::onHide()
{
  APP->getMap()->rem(&layer).rem(&source);
}
