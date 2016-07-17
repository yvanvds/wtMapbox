#include "stdafx.h"
#include "demo02_CreateClusters.h"
#include "mapboxApplication.h"
#include "wtMapbox.h"

CreateClusters::CreateClusters() {
  source.set("http://127.0.0.1:8080/earthquakes.geojson");
  source.cluster(50, 14);

  unclusteredLayer.set(&source);
  unclusteredLayer.icon.image("marker-15");

  clusterLayer[0].set(&source);
  clusterLayer[0].color(Wt::WColor("#f28cb1")).radius(18);
  clusterLayer[0].filter("['>=', 'point_count', 150]");

  clusterLayer[1].set(&source);
  clusterLayer[1].color(Wt::WColor("#f1f075")).radius(18);
  clusterLayer[1].filter("['all', ['>=', 'point_count', 20], ['<', 'point_count', 150]]");

  clusterLayer[2].set(&source);
  clusterLayer[2].color(Wt::WColor("#51bbd6")).radius(18);
  clusterLayer[2].filter("['all', ['>=', 'point_count', 0], ['<', 'point_count', 20]]");

  clusterCountLayer.set(&source);
  clusterCountLayer.text.label("{point_count}").size(12);
  clusterCountLayer.text.font("['DIN Offc Pro Medium', 'Arial Unicode MS Bold']");

  unclusteredCheck = new Wt::WCheckBox("Show unclustered", this);
  unclusteredCheck->setMargin(10);
  unclusteredCheck->setInline(false);
  unclusteredCheck->setChecked();
  unclusteredCheck->changed().connect(std::bind([=]() {
    unclusteredLayer.visible(unclusteredCheck->isChecked());
  }));

  clusterCheck[0] = new Wt::WCheckBox("Show Red Dots", this);
  clusterCheck[1] = new Wt::WCheckBox("Show Yellow Dots", this);
  clusterCheck[2] = new Wt::WCheckBox("Show Blue Dots", this);

  for (int i = 0; i < 3; i++) {
    clusterCheck[i]->setMargin(10);
    clusterCheck[i]->setChecked();
    clusterCheck[i]->setInline(false);
    clusterCheck[i]->changed().connect(std::bind([=]() {
      clusterLayer[i].visible(clusterCheck[i]->isChecked());
    }));
  }  

  clusterCountCheck = new Wt::WCheckBox("Show Counters", this);
  clusterCountCheck->setMargin(10);
  clusterCountCheck->setChecked();
  clusterCountCheck->setInline(false);
  clusterCountCheck->changed().connect(std::bind([=]() {
    clusterCountLayer.visible(clusterCountCheck->isChecked());
  }));
}

void CreateClusters::onShow() {
  // reset stuff
  unclusteredLayer.visible(true);
  unclusteredCheck->setChecked();
  clusterCountLayer.visible(true);
  clusterCountCheck->setChecked();

  for (int i = 0; i < 3; i++) {
    clusterLayer[i].visible(true);
    clusterCheck[i]->setChecked();
  }
  
  // change style and add layers
  APP->getMap()->setMapStyle(MapBox::MAPSTYLE::Dark, true);
  APP->getMap()->add(&source);
  APP->getMap()->add(&unclusteredLayer);
  APP->getMap()->add(&clusterLayer[0]);
  APP->getMap()->add(&clusterLayer[1]);
  APP->getMap()->add(&clusterLayer[2]);
  APP->getMap()->add(&clusterCountLayer);
  APP->getMap()->easeTo(MapBox::Coordinate(38.620655, -118.411719), 3, 1000);
  APP->getMap()->applyMapStyle();
}

void CreateClusters::onHide() {
  APP->getMap()->rem(&source);
  APP->getMap()->rem(&unclusteredLayer);
  APP->getMap()->rem(&clusterLayer[0]);
  APP->getMap()->rem(&clusterLayer[1]);
  APP->getMap()->rem(&clusterLayer[2]);
  APP->getMap()->rem(&clusterCountLayer);
}