#include "demo21_DataDrivenColors.h"
#include "stdafx.h"
#include "mapboxApplication.h"

using namespace Wt::Json;

DataDrivenColors::DataDrivenColors()
{
  source.set("mapbox://examples.8fgz4egr");
  layer.set(&source);
  layer.sourceLayer("sf2010");

  // constructing json objects works, but the syntax is not very nice
  Object radius;
  radius["base"] = Value(1.75);
  radius["stops"] = Value(ArrayType);
  Array & arr = radius["stops"];
  {
    arr.push_back(Value(ArrayType));
    Array & back = (Array &)arr.back();
    back.push_back(12);
    back.push_back(2);
  }
  {
    arr.push_back(Value(ArrayType));
    Array & back = (Array &)arr.back();
    back.push_back(22);
    back.push_back(180);
  }
  layer.radius(radius);

  Object color;
  color["property"] = Value(Wt::WString("ethnicity"));
  color["type"] = Value(Wt::WString("categorical"));
  color["stops"] = Value(ArrayType);
  Array & arr2 = color["stops"];
  {
    arr2.push_back(Value(ArrayType));
    Array & back = (Array &)arr2.back();
    back.push_back(Value(Wt::WString("White")));
    back.push_back(Value(Wt::WString("#fbb03b")));
  }
  {
    arr2.push_back(Value(ArrayType));
    Array & back = (Array &)arr2.back();
    back.push_back(Value(Wt::WString("Black")));
    back.push_back(Value(Wt::WString("#223b53")));
  }
  {
    arr2.push_back(Value(ArrayType));
    Array & back = (Array &)arr2.back();
    back.push_back(Value(Wt::WString("Hispanic")));
    back.push_back(Value(Wt::WString("#e55e5e")));
  }
  {
    arr2.push_back(Value(ArrayType));
    Array & back = (Array &)arr2.back();
    back.push_back(Value(Wt::WString("Asian")));
    back.push_back(Value(Wt::WString("#3bb2d0")));
  }
  {
    arr2.push_back(Value(ArrayType));
    Array & back = (Array &)arr2.back();
    back.push_back(Value(Wt::WString("Other")));
    back.push_back(Value(Wt::WString("#ccc")));
  }

  layer.color(color);
}

void DataDrivenColors::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Light, true);
  APP->getMap()->center(MapBox::Coordinate(37.753574, -122.447303)).zoom(12);
  APP->getMap()->add(&source);
  APP->getMap()->add(&layer);
  APP->getMap()->applyMapStyle();
}

void DataDrivenColors::onHide()
{
  APP->getMap()->rem(&source);
  APP->getMap()->rem(&layer);
}
