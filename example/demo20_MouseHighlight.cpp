#include "demo20_MouseHighlight.h"
#include "stdafx.h"
#include "mapboxApplication.h"

MouseHighlight::MouseHighlight()
{
  source.set("https://d2ad6b4ur7yvpq.cloudfront.net/naturalearth-3.3.0/ne_110m_admin_1_states_provinces.geojson");

  fills.set(&source);
  fills.color(Wt::WColor("#627BC1"));
  fills.opacity(0.5);

  borders.set(&source);
  borders.color(Wt::WColor("#627BC1"));
  borders.width(2);

  hover.set(&source);
  hover.color(Wt::WColor("#627BC1"));
  hover.opacity(1);
  hover.filter("['==', 'name', '']");

  // client side code
  mouseMove.trigger(MapBox::EVENT::MouseMove).code("function(e) {"
    " var features = " + APP->getMap()->jsRef() + ".map.queryRenderedFeatures(e.point, { layers: ['" + fills.id() + "'] });"
    " if (features.length) {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', features[0].properties.name]);"
    " } else {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', '']);"
    " }"
  "}"
  );

  mouseOut.trigger(MapBox::EVENT::MouseOut).code("function() {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', '']);"
   "}"
  );
}

void MouseHighlight::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->add(&source).add(&fills).add(&borders).add(&hover);
  APP->getMap()->center(MapBox::Coordinate(37.830348, -100.486052)).zoom(2);
  APP->getMap()->add(mouseMove).add(mouseOut);
  APP->getMap()->applyMapStyle();
}

void MouseHighlight::onHide()
{
  APP->getMap()->rem(&fills).rem(&borders).rem(&hover).rem(&source);
  // TODO: is this the most efficient way to unbind a function?
  APP->getMap()->rem(mouseMove).rem(mouseOut);
}
