#include "demo19_InfoPopup.h"
#include "stdafx.h"
#include "mapboxApplication.h"

using namespace MapBox;

InfoPopup::InfoPopup()
{
  resize(270, 400);
  Wt::WText * text = new Wt::WText("Click on a marker to open a popup.", this);
  text->setMargin(10);

  createCollection();
  source.set(&collection);
  layer.set(&source);
  layer.icon.image("{icon}-15");
  layer.icon.size(1.5);
  layer.icon.allowOverlap(true);

  // You could do all of this on the server side (and it would look more readable),
  // but there's no reason to send all this data back and forth over the network.
  click.trigger(EVENT::Click).code(
  "function (e) {"
    "var features = " + APP->getMap()->jsRef() + ".map.queryRenderedFeatures(e.point, { layers: ['" + layer.id() + "'] });"

    "if (!features.length) {"
       "return;"
    "}"

    "var feature = features[0];"

    "" + APP->getMap()->jsRef() + ".popup = new mapboxgl.Popup()"
    ".setLngLat(feature.geometry.coordinates)"
    ".setHTML(feature.properties.description)"
    ".addTo(" + APP->getMap()->jsRef() + ".map);"
  "}"
  );

  move.trigger(EVENT::MouseMove).code(
    "function(e) {"
    "  var features = map.queryRenderedFeatures(e.point, { layers: ['" + layer.id() + "'] });"
    "  " + APP->getMap()->jsRef() + ".map.getCanvas().style.cursor = (features.length) ? 'pointer' : '';"
    "}"
  );
}

void InfoPopup::onShow()
{
  APP->getMap()->setMapStyle(MAPSTYLE::Streets, true);
  APP->getMap()->add(&source).add(&layer);
  APP->getMap()->center(Coordinate(38.907, -77.04)).zoom(11.15);
  APP->getMap()->add(click).add(move);
  APP->getMap()->applyMapStyle();
}

void InfoPopup::onHide()
{
  APP->getMap()->rem(&layer).rem(&source);
  APP->getMap()->rem(click).rem(move);
}

void InfoPopup::createCollection()
{
  GFeature feature;
  feature.setProperty("description", "<strong>Make it Mount Pleasant</strong><p><a href=\"http://www.mtpleasantdc.com/makeitmtpleasant\" target=\"_blank\" title=\"Opens in a new window\">Make it Mount Pleasant</a> is a handmade and vintage market and afternoon of live entertainment and kids activities. 12:00-6:00 p.m.</p>");
  feature.setProperty("icon", "theatre");
  feature.geometry(GPoint(38.931567, -77.038659));
  collection.add(feature);

  feature.setProperty("description", "<strong>Mad Men Season Five Finale Watch Party</strong><p>Head to Lounge 201 (201 Massachusetts Avenue NE) Sunday for a <a href=\"http://madmens5finale.eventbrite.com/\" target=\"_blank\" title=\"Opens in a new window\">Mad Men Season Five Finale Watch Party</a>, complete with 60s costume contest, Mad Men trivia, and retro food and drink. 8:00-11:00 p.m. $10 general admission, $20 admission and two hour open bar.</p>");
  feature.setProperty("icon", "theatre");
  feature.geometry(GPoint(38.894651, -77.003168));
  collection.add(feature);

  feature.setProperty("description", "<strong>Big Backyard Beach Bash and Wine Fest</strong><p>EatBar (2761 Washington Boulevard Arlington VA) is throwing a <a href=\"http://tallulaeatbar.ticketleap.com/2012beachblanket/\" target=\"_blank\" title=\"Opens in a new window\">Big Backyard Beach Bash and Wine Fest</a> on Saturday, serving up conch fritters, fish tacos and crab sliders, and Red Apron hot dogs. 12:00-3:00 p.m. $25.grill hot dogs.</p>");
  feature.setProperty("icon", "bar");
  feature.geometry(GPoint(38.881189, -77.090372));
  collection.add(feature);

  feature.setProperty("description", "<strong>Ballston Arts & Crafts Market</strong><p>The <a href=\"http://ballstonarts-craftsmarket.blogspot.com/\" target=\"_blank\" title=\"Opens in a new window\">Ballston Arts & Crafts Market</a> sets up shop next to the Ballston metro this Saturday for the first of five dates this summer. Nearly 35 artists and crafters will be on hand selling their wares. 10:00-4:00 p.m.</p>");
  feature.setProperty("icon", "art-gallery");
  feature.geometry(GPoint(38.882342, -77.111561));
  collection.add(feature);

  feature.setProperty("description", "<strong>Seersucker Bike Ride and Social</strong><p>Feeling dandy? Get fancy, grab your bike, and take part in this year's <a href=\"http://dandiesandquaintrelles.com/2012/04/the-seersucker-social-is-set-for-june-9th-save-the-date-and-start-planning-your-look/\" target=\"_blank\" title=\"Opens in a new window\">Seersucker Social</a> bike ride from Dandies and Quaintrelles. After the ride enjoy a lawn party at Hillwood with jazz, cocktails, paper hat-making, and more. 11:00-7:00 p.m.</p>");
  feature.setProperty("icon", "bicycle");
  feature.geometry(GPoint(38.943951, -77.052477));
  collection.add(feature);

  feature.setProperty("description", "<strong>Capital Pride Parade</strong><p>The annual <a href=\"http://www.capitalpride.org/parade\" target=\"_blank\" title=\"Opens in a new window\">Capital Pride Parade</a> makes its way through Dupont this Saturday. 4:30 p.m. Free.</p>");
  feature.setProperty("icon", "star");
  feature.geometry(GPoint(38.909664, -77.043444));
  collection.add(feature);

  feature.setProperty("description", "<strong>Muhsinah</strong><p>Jazz-influenced hip hop artist <a href=\"http://www.muhsinah.com\" target=\"_blank\" title=\"Opens in a new window\">Muhsinah</a> plays the <a href=\"http://www.blackcatdc.com\">Black Cat</a> (1811 14th Street NW) tonight with <a href=\"http://www.exitclov.com\" target=\"_blank\" title=\"Opens in a new window\">Exit Clov</a> and <a href=\"http://godsilla.bandcamp.com\" target=\"_blank\" title=\"Opens in a new window\">Gods’illa</a>. 9:00 p.m. $12.</p>");
  feature.setProperty("icon", "music");
  feature.geometry(GPoint(38.914581, -77.031706));
  collection.add(feature);

  feature.setProperty("description", "<strong>A Little Night Music</strong><p>The Arlington Players' production of Stephen Sondheim's  <a href=\"http://www.thearlingtonplayers.org/drupal-6.20/node/4661/show\" target=\"_blank\" title=\"Opens in a new window\"><em>A Little Night Music</em></a> comes to the Kogod Cradle at The Mead Center for American Theater (1101 6th Street SW) this weekend and next. 8:00 p.m.</p>");
  feature.setProperty("icon", "music");
  feature.geometry(GPoint(38.878241, -77.020945));
  collection.add(feature);

  feature.setProperty("description", "<strong>Truckeroo</strong><p><a href=\"http://www.truckeroodc.com/www/\" target=\"_blank\">Truckeroo</a> brings dozens of food trucks, live music, and games to half and M Street SE (across from Navy Yard Metro Station) today from 11:00 a.m. to 11:00 p.m.</p>");
  feature.setProperty("icon", "music");
  feature.geometry(GPoint(38.876516, -77.007481));
  collection.add(feature);
}
