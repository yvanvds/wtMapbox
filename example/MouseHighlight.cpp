#include "MouseHighlight.h"
#include "stdafx.h"
#include "mapboxApplication.h"

MouseHighlight::MouseHighlight()
{
  source.setFromURL("https://d2ad6b4ur7yvpq.cloudfront.net/naturalearth-3.3.0/ne_110m_admin_1_states_provinces.geojson");

  fills.setSource(&source);
  fills.color(Wt::WColor("#627BC1"));
  fills.opacity(0.5);

  borders.setSource(&source);
  borders.color(Wt::WColor("#627BC1"));
  borders.width(2);

  hover.setSource(&source);
  hover.color(Wt::WColor("#627BC1"));
  hover.opacity(1);
  hover.setFilter("['==', 'name', '']");

  // client side code
  // TODO: this works, but it is very prone to errors!
  mouseMoveFunction = "function(e) {"
    " var features = " + APP->getMap()->jsRef() + ".map.queryRenderedFeatures(e.point, { layers: ['" + fills.id() + "'] });"
    " if (features.length) {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', features[0].properties.name]);"
    " } else {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', '']);"
    " }"
  "}";

  mouseOutFunction = "function() {"
    "    " + APP->getMap()->jsRef() + ".map.setFilter('" + hover.id() + "', ['==', 'name', '']);"
   "}";
}

void MouseHighlight::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->addSource(&source).addLayer(&fills).addLayer(&borders).addLayer(&hover);
  APP->getMap()->center(MapBox::Coordinate(37.830348, -100.486052)).zoom(2);
  APP->getMap()->addJSListener("mousemove", "MouseMoveDemo", mouseMoveFunction).addJSListener("mouseout", "MouseOutDemo", mouseOutFunction);
  APP->getMap()->applyMapStyle();
}

void MouseHighlight::onHide()
{
  APP->getMap()->removeLayer(&fills).removeLayer(&borders).removeLayer(&hover).removeSource(&source);
  // TODO: is this the most efficient way to unbind a function?
  APP->getMap()->remJSListener("mousemove", "MouseMoveDemo").remJSListener("mouseout", "MouseOutDemo");
}
