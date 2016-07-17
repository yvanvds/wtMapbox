#include "stdafx.h"
#include "demo18_FeatureOnClick.h"
#include "mapboxApplication.h"

FeatureOnClick::FeatureOnClick()
{
  source.set("https://d2ad6b4ur7yvpq.cloudfront.net/naturalearth-3.3.0/ne_110m_admin_1_states_provinces_shp.geojson");
  layer.set(&source);
  layer.color(Wt::WColor(200, 100, 240));
  layer.outlineColor(Wt::WColor(0, 255, 0));
  layer.opacity(0.5);

  resize(270, 400);
  text = new Wt::WText(this);
  
  popup = new MapBox::Popup(this);

  mouseMove.trigger(MapBox::EVENT::MouseMove).code(
    "function(e) {"
    "  var features = map.queryRenderedFeatures(e.point, { layers: ['" + layer.id() + "'] });"
    "  " + APP->getMap()->jsRef() + ".map.getCanvas().style.cursor = (features.length) ? 'pointer' : '';"
    "}"
  );
}

void FeatureOnClick::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  
  // signal to collect coordinate
  connection = APP->getMap()->clicked().connect(std::bind([=](const MapBox::Coordinate & e) {
    coordinate = e;
  }, std::placeholders::_1));
  
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(MapBox::Coordinate(38.907, -100.04)).zoom(3);
  
  // signale to collect feature
  APP->getMap()->clickedFeature(layer.id()).connect(std::bind([=](const Wt::WString & s) {
    
    // This is neat for getting all info on a location, but a feature can
    // hold a lot of information. The parser is probably not the fastest either, so this
    // could slow down the application.
    if (feature.set(s)) {
      const Wt::Json::Object & properties = feature.properties();
      popup->pos(coordinate);
      popup->setHTML(properties.get("name"));
      popup->addTo(*APP->getMap());
    }

  }, std::placeholders::_1));
  APP->getMap()->enableClickedFeature(true);

  // add mousemove handler to change cursor on features
  APP->getMap()->add(mouseMove);

  APP->getMap()->applyMapStyle();
}

void FeatureOnClick::onHide()
{
  APP->getMap()->clicked().disconnect(connection);
  APP->getMap()->rem(&layer).rem(&source);
  APP->getMap()->enableClickedFeature(false);
  APP->getMap()->rem(mouseMove);
  popup->remove();
}
