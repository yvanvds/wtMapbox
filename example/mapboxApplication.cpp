#include "mapboxApplication.h"

mapboxApplication::mapboxApplication(const WEnvironment & env) : WApplication(env)
{
  if (appRoot().empty()) {
    std::cerr << "!!!!!!!!!!" << std::endl
      << "!! Warning: read the README.md file for hints on deployment,"
      << " the approot looks suspect!" << std::endl
      << "!!!!!!!!!!" << std::endl;
  }

  setTheme(new WBootstrapTheme());
  this->useStyleSheet(WLink("wtMapExample.css"));

  setTitle("Mapbox Examples");

  WContainerWidget * mainContent = new WContainerWidget(root());
  mainContent->setStyleClass("examplemap");
  map = new MapBox::Map(mainContent);
  map->setMapStyle(MapBox::MAPSTYLE::Streets);
  map->setZoom(14);
  map->setCenter(MapBox::Coordinate(51.515823, -0.124331));

  // add all controls
  map->addNavigationControl();
  map->addGeoLocateControl();
  map->addGeoCoderControl();

  menuBar = new MenuBar(root());

}

