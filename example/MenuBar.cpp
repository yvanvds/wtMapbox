#include "stdafx.h"
#include "MenuBar.h"
#include "mapboxApplication.h"

// demos
#include "Demo.h"
#include "demo01_DisplayMap.h"
#include "demo02_CreateClusters.h"
#include "demo03_MapStyle.h"
#include "demo04_Heatmap.h"
#include "demo05_HeightLines.h"
#include "demo06_RasterTiles.h"
#include "demo07_FitBounds.h"
#include "demo08_SetLanguage.h"
#include "demo09_PitchAndBearing.h"
#include "demo10_ChangeColors.h"
#include "demo11_LayerOrder.h"
#include "demo12_GeoJSONLine.h"
#include "demo13_GeoJSONPoly.h"
#include "demo14_GeoJSONPoint.h"
#include "demo15_GetCoordinates.h"
#include "demo16_DisplayPopup.h"
#include "demo17_FeaturesBelowMouse.h"
#include "demo18_FeatureOnClick.h"
#include "demo19_InfoPopup.h"
#include "demo20_MouseHighlight.h"
#include "demo21_DataDrivenColors.h"
#include "demo22_AddImage.h"
#include "demo23_AddVideo.h"

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
  cb->addItem("Draw GeoJSON points");
  cb->addItem("Get coordinates from mouse");
  cb->addItem("Display a Popup");
  cb->addItem("Get features below mouse pointer");
  cb->addItem("Get feature on click");
  cb->addItem("Info in Popup");
  cb->addItem("Mouse Highlight");
  cb->addItem("Data Driven Colors");
  cb->addItem("Add an image");
  cb->addItem("Add a video");

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
  stack->addWidget(new GeoJSONPoint());
  stack->addWidget(new GetCoordinates());
  stack->addWidget(new DisplayPopup());
  stack->addWidget(new FeaturesBelowMouse());
  stack->addWidget(new FeatureOnClick());
  stack->addWidget(new InfoPopup());
  stack->addWidget(new MouseHighlight());
  stack->addWidget(new DataDrivenColors());
  stack->addWidget(new AddImage());
  stack->addWidget(new AddVideo());

  cb->changed().connect(std::bind([=]() {
    int choice = cb->currentIndex();
    if (choice < stack->count()) {
      ((Demo *)stack->currentWidget())->onHide();
      stack->setCurrentIndex(choice);
      ((Demo *)stack->currentWidget())->onShow();
    }
  }));

}


