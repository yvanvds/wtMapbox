#include "DisplayPopup.h"
#include "stdafx.h"
#include "mapboxApplication.h"

DisplayPopup::DisplayPopup()
{
  popup = new MapBox::Popup(this, true, false);
  popup->setHTML("<h1>Hello World!</h1>");
  popup->pos(MapBox::Coordinate(50.883198, 4.712435));
}

void DisplayPopup::onShow()
{
  popup->addTo(*APP->getMap());
  APP->getMap()->center(MapBox::Coordinate(50.883198, 4.712435)).zoom(3);
}

void DisplayPopup::onHide()
{
  popup->remove();
}


