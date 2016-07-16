#include "stdafx.h"
#include "FeaturesBelowMouse.h"
#include "mapboxApplication.h"

FeaturesBelowMouse::FeaturesBelowMouse()
{
  resize(290, 400);

  Wt::WText * text = new Wt::WText(this);

  mouseMoveFunction = "function(e) {"
    "var features = " + APP->getMap()->jsRef() + ".map.queryRenderedFeatures(e.point);"
    "document.getElementById('" + text->id() + "').innerHTML = '<pre>' + JSON.stringify(features, null, 2) + '</pre>';"
    "}";
}

void FeaturesBelowMouse::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->center(MapBox::Coordinate(50.883198, 4.712435)).zoom(3);
  APP->getMap()->addJSListener("mousemove", "MouseMoveDemo", mouseMoveFunction);
  APP->getMap()->applyMapStyle();
}

void FeaturesBelowMouse::onHide()
{
  APP->getMap()->remJSListener("mousemove", "MouseMoveDemo");
}