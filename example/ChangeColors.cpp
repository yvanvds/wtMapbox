#include "stdafx.h"
#include "ChangeColors.h"
#include "mapboxApplication.h"

ChangeColors::ChangeColors()
{
  Wt::WComboBox * cb = new Wt::WComboBox(this);
  cb->setCurrentIndex(0);
  cb->setMargin(10);
  cb->setInline(false);
  cb->addItem("building");
  cb->addItem("water");

  Wt::WPushButton * button = new Wt::WPushButton("Red", this);
  button->setMargin(10);
  button->setInline(false);
  button->setStyleClass("btn-danger");
  button->clicked().connect(std::bind([=]() {
    APP->getMap()->setPaintProperty(cb->currentText(), "fill-color", "#ffaaaa");
  }));

  button = new Wt::WPushButton("Green", this);
  button->setMargin(10);
  button->setInline(false);
  button->setStyleClass("btn-success");
  button->clicked().connect(std::bind([=]() {
    APP->getMap()->setPaintProperty(cb->currentText(), "fill-color", "#aaffaa");
  }));

  button = new Wt::WPushButton("Blue", this);
  button->setMargin(10);
  button->setInline(false);
  button->setStyleClass("btn-primary");
  button->clicked().connect(std::bind([=]() {
    APP->getMap()->setPaintProperty(cb->currentText(), "fill-color", "#aaaaff");
  }));
}

void ChangeColors::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Light, true);
  APP->getMap()->center(MapBox::Coordinate(45.4385, 12.338)).zoom(17.4);
  APP->getMap()->applyMapStyle();
}

void ChangeColors::onHide()
{
}
