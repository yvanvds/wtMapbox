#include "stdafx.h"
#include "demo05_HeightLines.h"
#include "mapboxApplication.h"

HeightLines::HeightLines()
{
  museums.set("mapbox://mapbox.2opop9hr");
  contours.set("mapbox://mapbox.mapbox-terrain-v2");

  museumLayer.set(&museums);
  museumLayer.sourceLayer("museum-cusco");
  museumLayer.radius(8);
  museumLayer.color(Wt::WColor(55, 148, 179));

  contourLayer.set(&contours);
  contourLayer.sourceLayer("contour");
  contourLayer.join(MapBox::JOIN::Round);
  contourLayer.cap(MapBox::CAP::Round);
  contourLayer.color(Wt::WColor("#877b59"));
  contourLayer.width(1);

  resize(250, 100);

  Wt::WVBoxLayout * vbox = new Wt::WVBoxLayout();
  setLayout(vbox);

  Wt::WHBoxLayout * hbox = new Wt::WHBoxLayout();
  vbox->addLayout(hbox);

  Wt::WText * t = new Wt::WText("Width: ", this);
  t->setMargin(10);
  hbox->addWidget(t);

  Wt::WSlider * slider = new Wt::WSlider(this);
  slider->resize(200, 12);
  slider->setMinimum(1);
  slider->setMaximum(10);
  slider->setValue(1);
  hbox->addWidget(slider);

  slider->valueChanged().connect(std::bind([=]() {
    contourLayer.width(slider->value());
  }));

  hbox = new Wt::WHBoxLayout();
  vbox->addLayout(hbox);

  t = new Wt::WText("Blur: ", this);
  t->setMargin(10);
  hbox->addWidget(t);

  slider = new Wt::WSlider(this);
  slider->resize(200, 12);
  slider->setMinimum(0);
  slider->setMaximum(10);
  slider->setValue(0);
  hbox->addWidget(slider);

  slider->valueChanged().connect(std::bind([=]() {
    contourLayer.blur(slider->value());
  }));

}

void HeightLines::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->add(&museums);
  APP->getMap()->add(&contours);
  APP->getMap()->add(&museumLayer);
  APP->getMap()->add(&contourLayer);
  APP->getMap()->easeTo(MapBox::Coordinate(-13.517379300798098 ,-71.97722138410576), 15, 1000);
  APP->getMap()->applyMapStyle();
}

void HeightLines::onHide()
{
  APP->getMap()->rem(&museums);
  APP->getMap()->rem(&contours);
  APP->getMap()->rem(&museumLayer);
  APP->getMap()->rem(&contourLayer);
}
