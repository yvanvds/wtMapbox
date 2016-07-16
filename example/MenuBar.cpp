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
#include "ChangeColors.h"
#include "LayerOrder.h"
#include "GeoJSONLine.h"
#include "GeoJSONPoly.h"
#include "MouseHighlight.h"
#include "GeoJSONPoint.h"
#include "GetCoordinates.h"
#include "DisplayPopup.h"

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
  cb->addItem("Change map colors");
  cb->addItem("Layer Order");
  cb->addItem("Add a GeoJSON line");
  cb->addItem("Add a GeoJSON polygon");
  cb->addItem("Mouse Highlight");
  cb->addItem("Draw GeoJSON points");
  cb->addItem("Get coordinates from mouse");
  cb->addItem("Display a Popup");
  
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
  stack->addWidget(new ChangeColors());
  stack->addWidget(new LayerOrder());
  stack->addWidget(new GeoJSONLine());
  stack->addWidget(new GeoJSONPoly());
  stack->addWidget(new MouseHighlight());
  stack->addWidget(new GeoJSONPoint());
  stack->addWidget(new GetCoordinates());
  stack->addWidget(new DisplayPopup());

  cb->changed().connect(std::bind([=]() {
    int choice = cb->currentIndex();
    if (choice < stack->count()) {
      ((Demo *)stack->currentWidget())->onHide();
      stack->setCurrentIndex(choice);
      ((Demo *)stack->currentWidget())->onShow();
    }
  }));

}


