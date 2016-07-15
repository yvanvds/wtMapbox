#include "stdafx.h"
#include "CreateClusters.h"
#include "mapboxApplication.h"
#include "wtMapbox.h"

CreateClusters::CreateClusters() {
  source.setFromURL("http://127.0.0.1:8080/earthquakes.geojson");
  source.setCluster(50, 14);

  unclusteredLayer.setSource(&source);
  unclusteredLayer.icon.image("'marker-15'");

  clusterLayer[0].setSource(&source);
  clusterLayer[0].color(Wt::WColor("#f28cb1")).radius(18);
  clusterLayer[0].setFilter("['>=', 'point_count', 150]");

  clusterLayer[1].setSource(&source);
  clusterLayer[1].color(Wt::WColor("#f1f075")).radius(18);
  clusterLayer[1].setFilter("['all', ['>=', 'point_count', 20], ['<', 'point_count', 150]]");

  clusterLayer[2].setSource(&source);
  clusterLayer[2].color(Wt::WColor("#51bbd6")).radius(18);
  clusterLayer[2].setFilter("['all', ['>=', 'point_count', 0], ['<', 'point_count', 20]]");

  clusterCountLayer.setSource(&source);
  clusterCountLayer.text.label("'{point_count}'").size(12);
  clusterCountLayer.text.font("[\"DIN Offc Pro Medium\", \"Arial Unicode MS Bold\"]");

  unclusteredCheck = new Wt::WCheckBox("Show unclustered", this);
  unclusteredCheck->setMargin(10);
  unclusteredCheck->setInline(false);
  unclusteredCheck->setChecked();
  unclusteredCheck->changed().connect(std::bind([=]() {
    unclusteredLayer.setVisible(unclusteredCheck->isChecked());
  }));

  clusterCheck[0] = new Wt::WCheckBox("Show Red Dots", this);
  clusterCheck[1] = new Wt::WCheckBox("Show Yellow Dots", this);
  clusterCheck[2] = new Wt::WCheckBox("Show Blue Dots", this);

  for (int i = 0; i < 3; i++) {
    clusterCheck[i]->setMargin(10);
    clusterCheck[i]->setChecked();
    clusterCheck[i]->setInline(false);
    clusterCheck[i]->changed().connect(std::bind([=]() {
      clusterLayer[i].setVisible(clusterCheck[i]->isChecked());
    }));
  }  

  clusterCountCheck = new Wt::WCheckBox("Show Counters", this);
  clusterCountCheck->setMargin(10);
  clusterCountCheck->setChecked();
  clusterCountCheck->setInline(false);
  clusterCountCheck->changed().connect(std::bind([=]() {
    clusterCountLayer.setVisible(clusterCountCheck->isChecked());
  }));
}

void CreateClusters::onShow() {
  // reset stuff
  unclusteredLayer.setVisible(true);
  unclusteredCheck->setChecked();
  clusterCountLayer.setVisible(true);
  clusterCountCheck->setChecked();

  for (int i = 0; i < 3; i++) {
    clusterLayer[i].setVisible(true);
    clusterCheck[i]->setChecked();
  }
  
  // change style and add layers
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE_DARK, true);
  APP->getMap()->addSource(&source);
  APP->getMap()->addLayer(&unclusteredLayer);
  APP->getMap()->addLayer(&clusterLayer[0]);
  APP->getMap()->addLayer(&clusterLayer[1]);
  APP->getMap()->addLayer(&clusterLayer[2]);
  APP->getMap()->addLayer(&clusterCountLayer);
  APP->getMap()->easeTo(MapBox::Coordinate(38.620655, -118.411719), 3, 1000);
  APP->getMap()->applyMapStyle();
}

void CreateClusters::onHide() {
  APP->getMap()->removeSource(&source);
  APP->getMap()->removeLayer(&unclusteredLayer);
  APP->getMap()->removeLayer(&clusterLayer[0]);
  APP->getMap()->removeLayer(&clusterLayer[1]);
  APP->getMap()->removeLayer(&clusterLayer[2]);
  APP->getMap()->removeLayer(&clusterCountLayer);
}