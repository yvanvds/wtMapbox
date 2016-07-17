#include "stdafx.h"
#include "demo04_Heatmap.h"
#include "mapboxApplication.h"

Heatmap::Heatmap()
{
  source.set("http://127.0.0.1:8080/earthquakes.geojson");
  source.cluster(20, 15);


  layer[0].set(&source);
  layer[0].color(Wt::WColor("green"));
  layer[0].radius(70).blur(1);
  layer[0].filter("['all', ['>=', 'point_count', 0], ['<', 'point_count', 20]]");

  layer[1].set(&source);
  layer[1].color(Wt::WColor("orange"));
  layer[1].radius(70).blur(1);
  layer[1].filter("['all', ['>=', 'point_count', 20], ['<', 'point_count', 200]]");

  layer[2].set(&source);
  layer[2].color(Wt::WColor("red"));
  layer[2].radius(70).blur(1);
  layer[2].filter("['>=', 'point_count', 200]");

  layer[3].set(&source);
  layer[3].color(Wt::WColor(0, 255, 0, 125));
  layer[3].radius(20).blur(1);
  layer[3].filter("['!=', 'cluster', true]");

  new Wt::WText("Opacity: ", this);
  Wt::WSlider * slider = new Wt::WSlider(this);
  slider->resize(200, 12);
  slider->setMinimum(0);
  slider->setMaximum(100);
  slider->setValue(100);
  slider->valueChanged().connect(std::bind([=]() {
    float value = slider->value() / 100.f;
    layer[0].opacity(value);
    layer[1].opacity(value);
    layer[2].opacity(value);
    layer[3].opacity(value);
  }));
}

void Heatmap::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Dark, true);
  APP->getMap()->add(&source);
  APP->getMap()->add(&layer[0]);
  APP->getMap()->add(&layer[1]);
  APP->getMap()->add(&layer[2]);
  APP->getMap()->add(&layer[3]);
  APP->getMap()->easeTo(MapBox::Coordinate(18.609917, -72.324234), 3, 1000);
  APP->getMap()->applyMapStyle();
}

void Heatmap::onHide()
{
  APP->getMap()->rem(&source);
  APP->getMap()->rem(&layer[0]);
  APP->getMap()->rem(&layer[1]);
  APP->getMap()->rem(&layer[2]);
  APP->getMap()->rem(&layer[3]);
}
