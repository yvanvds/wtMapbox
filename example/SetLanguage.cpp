#include "stdafx.h"
#include "SetLanguage.h"
#include "mapboxApplication.h"

SetLanguage::SetLanguage()
{
  group = new Wt::WButtonGroup(this);
  Wt::WRadioButton * button;

  button = new Wt::WRadioButton("English", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 1);

  button = new Wt::WRadioButton("Chinese", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 2);

  button = new Wt::WRadioButton("French", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 3);

  button = new Wt::WRadioButton("Russian", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 4);

  button = new Wt::WRadioButton("German", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 5);

  button = new Wt::WRadioButton("Spanish", this);
  button->setInline(false);
  button->setMargin(10);
  group->addButton(button, 6);

  group->checkedChanged().connect(std::bind([=](Wt::WRadioButton * selection) {
    switch (group->id(selection)) {
    case 1: APP->getMap()->language("en"); break;
    case 2: APP->getMap()->language("zh"); break;
    case 3: APP->getMap()->language("fr"); break;
    case 4: APP->getMap()->language("ru"); break;
    case 5: APP->getMap()->language("de"); break;
    case 6: APP->getMap()->language("es"); break;
    }
  }, std::placeholders::_1));
}

void SetLanguage::onShow()
{
  group->setSelectedButtonIndex(-1);
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Light);
  APP->getMap()->center(MapBox::Coordinate(48, 16.05)).zoom(2.9).applyMapStyle();
}

void SetLanguage::onHide()
{
}
