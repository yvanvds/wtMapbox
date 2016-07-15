#include "stdafx.h"
#include "PitchAndBearing.h"
#include "mapboxApplication.h"

PitchAndBearing::PitchAndBearing()
{
  resize(250, 100);

  Wt::WVBoxLayout * vbox = new Wt::WVBoxLayout();
  setLayout(vbox);

  Wt::WHBoxLayout * hbox = new Wt::WHBoxLayout();
  vbox->addLayout(hbox);

  Wt::WText * t = new Wt::WText("Pitch: ", this);
  hbox->addWidget(t);

  Wt::WSlider * slider = new Wt::WSlider(this);
  hbox->addWidget(slider);

  slider->resize(200, 12);
  slider->setMinimum(0);
  slider->setMaximum(60);
  slider->setValue(0);
  slider->valueChanged().connect(std::bind([=]() {
    APP->getMap()->pitch(slider->value());
  }));

  hbox = new Wt::WHBoxLayout();
  vbox->addLayout(hbox);

  t = new Wt::WText("Bearing: ", this);
  hbox->addWidget(t);

  slider = new Wt::WSlider(this);
  hbox->addWidget(slider);

  slider->resize(200, 12);
  slider->setMinimum(0);
  slider->setMaximum(360);
  slider->setValue(0);
  slider->valueChanged().connect(std::bind([=]() {
    APP->getMap()->bearing(slider->value());
  }));
}

void PitchAndBearing::onShow()
{
}

void PitchAndBearing::onHide()
{
  APP->getMap()->pitch(0).bearing(0);
}
