#include "demo24_RealtimeData.h"
#include "stdafx.h"
#include "mapboxApplication.h"

RealtimeData::RealtimeData()
{
  source.set("https://wanderdrone.appspot.com/");
  layer.set(&source);
  layer.icon.image("rocket-15");

  timer = new Wt::WTimer(this);
  timer->setInterval(2000);
  timer->timeout().connect(this, &RealtimeData::timeout);
}

void RealtimeData::onShow()
{
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Streets, true);
  APP->getMap()->zoom(0);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->applyMapStyle();

  timer->start();
}

void RealtimeData::onHide()
{
  timer->stop();
  APP->getMap()->rem(&layer).rem(&source);
}

void RealtimeData::timeout() {
  source.set("https://wanderdrone.appspot.com/");
}