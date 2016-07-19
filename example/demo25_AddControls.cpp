#include "demo25_AddControls.h"
#include "stdafx.h"
#include "mapboxApplication.h"

AddControls::AddControls()
{
  navigation = new MapBox::Control(MapBox::CONTROL::Navigation, MapBox::TEXT_ANCHOR::TopRight, this);
  geoLocate = new MapBox::Control(MapBox::CONTROL::GeoLocate, MapBox::TEXT_ANCHOR::TopRight, this);
  geoCoder = new MapBox::Control(MapBox::CONTROL::GeoCoder, MapBox::TEXT_ANCHOR::BottomLeft, this);
  directions = new MapBox::Control(MapBox::CONTROL::Directions, MapBox::TEXT_ANCHOR::TopLeft, this);

  Wt::WCheckBox * checkbox = new Wt::WCheckBox("Navigation Control", this);
  checkbox->setMargin(10);
  checkbox->clicked().connect(std::bind([=]() {
    if (checkbox->isChecked()) {
      navigation->addTo(*APP->getMap());
    }
    else {
      navigation->remove();
    }
  }));

  new Wt::WBreak(this);

  checkbox = new Wt::WCheckBox("Geolocation Control", this);
  checkbox->setMargin(10);
  checkbox->clicked().connect(std::bind([=]() {
    if (checkbox->isChecked()) {
      geoLocate->addTo(*APP->getMap());
    }
    else {
      geoLocate->remove();
    }
  }));

  new Wt::WBreak(this);

  checkbox = new Wt::WCheckBox("Geocoder Control", this);
  checkbox->setMargin(10);
  checkbox->clicked().connect(std::bind([=]() {
    if (checkbox->isChecked()) {
      geoCoder->addTo(*APP->getMap());
    }
    else {
      geoCoder->remove();
    }
  }));

  new Wt::WBreak(this);

  checkbox = new Wt::WCheckBox("Directions Control", this);
  checkbox->setMargin(10);
  checkbox->clicked().connect(std::bind([=]() {
    if (checkbox->isChecked()) {
      directions->addTo(*APP->getMap());
    }
    else {
      directions->remove();
    }
  }));
  
}

void AddControls::onShow()
{
  // Directions api only works with mapstyles Streets and SatteliteStreets
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets);
}

void AddControls::onHide() {
}