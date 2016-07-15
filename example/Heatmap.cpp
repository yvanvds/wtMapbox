#include "stdafx.h"
#include "Heatmap.h"
#include "mapboxApplication.h"

Heatmap::Heatmap()
{
  source.setFromURL("http://127.0.0.1:8080/earthquakes.geojson");
  source.setCluster(20, 15);


  layer[0].setSource(&source);
  layer[0].color(Wt::WColor("green"));
  layer[0].radius(70).blur(1);
  layer[0].setFilter("['all', ['>=', 'point_count', 0], ['<', 'point_count', 20]]");

  layer[1].setSource(&source);
  layer[1].color(Wt::WColor("orange"));
  layer[1].radius(70).blur(1);
  layer[1].setFilter("['all', ['>=', 'point_count', 20], ['<', 'point_count', 200]]");

  layer[2].setSource(&source);
  layer[2].color(Wt::WColor("red"));
  layer[2].radius(70).blur(1);
  layer[2].setFilter("['>=', 'point_count', 200]");

  layer[3].setSource(&source);
  layer[3].color(Wt::WColor(0, 255, 0, 125));
  layer[3].radius(20).blur(1);
  layer[3].setFilter("['!=', 'cluster', true]");

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
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE_DARK, true);
  APP->getMap()->addSource(&source);
  APP->getMap()->addLayer(&layer[0]);
  APP->getMap()->addLayer(&layer[1]);
  APP->getMap()->addLayer(&layer[2]);
  APP->getMap()->addLayer(&layer[3]);
  APP->getMap()->easeTo(MapBox::Coordinate(18.609917, -72.324234), 3, 1000);
  APP->getMap()->applyMapStyle();
}

void Heatmap::onHide()
{
  APP->getMap()->removeSource(&source);
  APP->getMap()->removeLayer(&layer[0]);
  APP->getMap()->removeLayer(&layer[1]);
  APP->getMap()->removeLayer(&layer[2]);
  APP->getMap()->removeLayer(&layer[3]);
}
