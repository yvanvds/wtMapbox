#include "stdafx.h"
#include "FitBounds.h"
#include "mapboxApplication.h"

FitBounds::FitBounds()
{
  Wt::WPushButton * button = new Wt::WPushButton("Fly to Kenya", this);
  button->setInline(false);
  button->setStyleClass("btn-primary");
  button->setMargin(10);
  button->clicked().connect(std::bind([=]() {
    MapBox::Bounds bounds;
    bounds.leftDown = MapBox::Coordinate(-5.353521, 32.958984);
    bounds.rightUp = MapBox::Coordinate(5.615985, 43.50585);
    APP->getMap()->fitBounds(bounds);
  }));

  button = new Wt::WPushButton("Move to Brussels", this);
  button->setInline(false);
  button->setStyleClass("btn-primary");
  button->setMargin(10);
  button->clicked().connect(std::bind([=]() {
    MapBox::Bounds bounds;
    bounds.leftDown = MapBox::Coordinate(50.832701, 4.336266);
    bounds.rightUp = MapBox::Coordinate(50.858259, 4.370745);
    APP->getMap()->fitBounds(bounds, true, 10);
  }));

}

void FitBounds::onShow()
{
}

void FitBounds::onHide()
{
}
