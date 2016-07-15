#include "stdafx.h"
#include "MapStyle.h"
#include "mapboxApplication.h"

MapStyle::MapStyle()
{
  group = new Wt::WButtonGroup(this);
  Wt::WRadioButton * button;

  button = new Wt::WRadioButton("Streets", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 1);

  button = new Wt::WRadioButton("Outdoors", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 2);

  button = new Wt::WRadioButton("Light", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 3);

  button = new Wt::WRadioButton("Dark", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 4);

  button = new Wt::WRadioButton("Satellite", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 5);

  button = new Wt::WRadioButton("Satellite Streets", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 6);

  group->checkedChanged().connect(std::bind([=](Wt::WRadioButton * selection) {
    switch (group->id(selection)) {
      case 1: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_STREETS); break;
      case 2: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_OUTDOORS); break;
      case 3: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_LIGHT); break;
      case 4: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_DARK); break;
      case 5: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_SATELLITE); break;
      case 6: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_SATELLITE_STREETS); break;
    }
  }, std::placeholders::_1));
}

void MapStyle::onShow()
{
  group->setSelectedButtonIndex(-1);
}

void MapStyle::onHide()
{
}
