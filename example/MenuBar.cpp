#include "stdafx.h"
#include "MenuBar.h"
#include "mapboxApplication.h"

// demos
#include "Demo.h"
#include "DisplayMap.h"
#include "CreateClusters.h"
#include "MapStyle.h"
#include "Heatmap.h"
#include "HeightLines.h"
#include "RasterTiles.h"
#include "FitBounds.h"
#include "SetLanguage.h"
#include "PitchAndBearing.h"

MenuBar::MenuBar(WContainerWidget * parent) : WContainerWidget(parent)
{

  // create demo menu
  Wt::WComboBox *cb = new Wt::WComboBox(this);
  cb->addItem("Display a map");
  cb->addItem("Create and style clusters");
  cb->addItem("Change a map's style");
  cb->addItem("Create a heatmap from points");
  cb->addItem("Height Lines");
  cb->addItem("Raster Tiles");
  cb->addItem("Fit to Bounds");
  cb->addItem("Set Language");
  cb->addItem("Pitch and Bearing");
  
  cb->setCurrentIndex(0);
  cb->setMargin(10);

  // add all demo's to stack
  Wt::WStackedWidget * stack = new Wt::WStackedWidget(this);
  stack->addWidget(new DisplayMap());
  stack->addWidget(new CreateClusters());
  stack->addWidget(new MapStyle());
  stack->addWidget(new Heatmap());
  stack->addWidget(new HeightLines());
  stack->addWidget(new RasterTiles());
  stack->addWidget(new FitBounds());
  stack->addWidget(new SetLanguage());
  stack->addWidget(new PitchAndBearing());

  cb->changed().connect(std::bind([=]() {
    int choice = cb->currentIndex();
    if (choice < stack->count()) {
      ((Demo *)stack->currentWidget())->onHide();
      stack->setCurrentIndex(choice);
      ((Demo *)stack->currentWidget())->onShow();
    }
  }));

}


