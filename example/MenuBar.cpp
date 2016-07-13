#include "stdafx.h"
#include "MenuBar.h"
#include "mapboxApplication.h"


MenuBar::MenuBar(WContainerWidget * parent) : WContainerWidget(parent)
{
  heatmap = nullptr;

  setStyleClass("examplemenu");

  createDemo1();
  createDemo2();
  createDemo3();

}

void MenuBar::createDemo1() {
  demo1 = new WPanel(this);
  demo1->setTitle("Moving");
  demo1->addStyleClass("centered-example");
  demo1->setCollapsible(true);

  WContainerWidget * content = new WContainerWidget();
  demo1->setCentralWidget(content);

  WPushButton * goTo = new WPushButton("Ease to Leuven", content);
  goTo->clicked().connect(std::bind([=] {
    APP->getMap()->easeTo(MapBox::Coordinate(50.878999, 4.701645));
  }));

  WPushButton * flyTo = new WPushButton("Fly to London", content);
  flyTo->clicked().connect(std::bind([=] {
    APP->getMap()->flyTo(MapBox::Coordinate(51.504427, -0.144004));
  }));
}

void MenuBar::createDemo2() {
  demo2 = new WPanel(this);
  demo2->setTitle("Styles");
  demo2->addStyleClass("centered-example");
  demo2->setCollapsible(true);

  WContainerWidget * content = new WContainerWidget();
  demo2->setCentralWidget(content);

  WComboBox * cb = new Wt::WComboBox(content);
  cb->addItem("Streets");
  cb->addItem("Outdoors");
  cb->addItem("Light");
  cb->addItem("Dark");
  cb->addItem("Satellite");
  cb->addItem("Satellite Streets");

  cb->changed().connect(std::bind([=]() {
    switch (cb->currentIndex()) {
      case 0: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_STREETS); break;
      case 1: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_OUTDOORS); break;
      case 2: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_LIGHT); break;
      case 3: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_DARK); break;
      case 4: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_SATELLITE); break;
      case 5: APP->getMap()->setMapStyle(MapBox::MAPSTYLE_SATELLITE_STREETS); break;
    }
    
    // changing a map style removes all current layers. Update the 
    // overlays accordingly.
    if (heatmap != nullptr) {
      heatmap->setUnChecked();
    }
  }));
}

void MenuBar::createDemo3() {
  demo3 = new WPanel(this);
  demo3->setTitle("Overlays");
  demo3->addStyleClass("centered-example");
  demo3->setCollapsible(true);

  WContainerWidget * content = new WContainerWidget();
  demo3->setCentralWidget(content);

  // heatmap source and layers
  demo3Source.setFromURL("http://127.0.0.1:8080/earthquakes.geojson");
  demo3Source.setCluster(20, 15);
  

  demo3Layer1.setSource(&demo3Source);
  demo3Layer1.color(Wt::WColor("green"));
  demo3Layer1.radius(70).blur(1);
  demo3Layer1.setFilter("['all', ['>=', 'point_count', 0], ['<', 'point_count', 20]]");

  demo3Layer2.setSource(&demo3Source);
  demo3Layer2.color(Wt::WColor("orange"));
  demo3Layer2.radius(70).blur(1);
  demo3Layer2.setFilter("['all', ['>=', 'point_count', 20], ['<', 'point_count', 200]]");

  demo3Layer3.setSource(&demo3Source);
  demo3Layer3.color(Wt::WColor("red"));
  demo3Layer3.radius(70).blur(1);
  demo3Layer3.setFilter("['>=', 'point_count', 200]");

  demo3Layer4.setSource(&demo3Source);
  demo3Layer4.color(Wt::WColor(0,255,0,125));
  demo3Layer4.radius(20).blur(1);
  demo3Layer4.setFilter("['!=', 'cluster', true]");

  // checkbox to toggle heatmap. In fact the layer visibility function should
  // be used for this, but in the second demo it is possible to change the map style
  // which clear the current layers
  heatmap = new Wt::WCheckBox("Heatmap", content);
  heatmap->changed().connect(std::bind([=]() {
    if (heatmap->isChecked()) {   
      APP->getMap()->addSource(&demo3Source);
      APP->getMap()->addLayer(&demo3Layer1);
      APP->getMap()->addLayer(&demo3Layer2);
      APP->getMap()->addLayer(&demo3Layer3);
      APP->getMap()->addLayer(&demo3Layer4);
      APP->getMap()->easeTo(MapBox::Coordinate(18.609917, -72.324234), 3);
      
    }
    else {
      APP->getMap()->removeSource(&demo3Source);
      APP->getMap()->removeLayer(&demo3Layer1);
      APP->getMap()->removeLayer(&demo3Layer2);
      APP->getMap()->removeLayer(&demo3Layer3);
      APP->getMap()->removeLayer(&demo3Layer4);
    }
  }));

  // slider to change heatmap opacity
  new Wt::WBreak(content);
  new Wt::WText("Opacity: ", content);
  Wt::WSlider * slider = new Wt::WSlider(content);
  slider->resize    (200, 12);
  slider->setMinimum(0      );
  slider->setMaximum(100    );
  slider->setValue  (100    );
  slider->valueChanged().connect(std::bind([=]() {
    float value = slider->value() / 100.f;
    demo3Layer1.opacity(value);
    demo3Layer2.opacity(value);
    demo3Layer3.opacity(value);
    demo3Layer4.opacity(value);
  }));

}

