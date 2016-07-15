#pragma once

#include <vector>
#include <string>

#include "Coordinate.h"
#include "Layer.h"

namespace MapBox {

  // predefined mapbox styles
  namespace MAPSTYLE {
    const std::string Streets = "mapbox://styles/mapbox/streets-v9";
    const std::string Outdoors = "mapbox://styles/mapbox/outdoors-v9";
    const std::string Light = "mapbox://styles/mapbox/light-v9";
    const std::string Dark = "mapbox://styles/mapbox/dark-v9";
    const std::string Satellite = "mapbox://styles/mapbox/satellite-v9";
    const std::string SatelliteStreets = "mapbox://styles/mapbox/satellite-streets-v9";
  }

  // interactions
  const std::string I_SCROLLZOOM = "scrollZoom";
  const std::string I_BOXZOOM = "boxZoom";
  const std::string I_DRAGROTATE = "dragRotate";
  const std::string I_DRAGPAN = "dragPan";
  const std::string I_KEYBOARD = "keyboard";
  const std::string I_DOUBLECLICKZOOM = "doubleClickZoom";
  const std::string I_TOUCHZOOMROTATE = "touchZoomRotate";

  enum CONTROL_POS {
    TOPRIGHT,
    TOPLEFT,
    BOTTOMRIGHT,
    BOTTOMLEFT,
  };


  class Map : public Wt::WCompositeWidget
  {
  public:

    Map(Wt::WContainerWidget * parent = 0);
    virtual ~Map();

    /* Set a map zoom */
    Map & zoom(float level);   float zoom() C { return zoom_; }
    Map & resize();

    /* set a language (2 letter language code) */
    Map & language(C std::string & code); C std::string & language() C { return language_; }

    /* Set a map location */
    Map & center   (C Coordinate & coordinate); C Coordinate & center() C { return center_; }
    Map & easeTo   (C Coordinate & destination, int  zoom   = -1   , int   duration = -1                        );
    Map & flyTo    (C Coordinate & destination, int  zoom   = -1   , float curve    = 1.42, float speed   =  1.2);
    Map & fitBounds(C Bounds     & bounds     , bool linear = false, int   padding  = 0   , int   maxZoom = -1  );


    /* Replaces the map's style object with a new value. This is an URL string. Refer
       to mapbox api for syntax or use one of the predefined styles above.
       */
    Map & setMapStyle(const std::string & style, bool waitForApply = false); C std::string & mapStyle() C { return mapStyle_; }

    /* Once the map is rendered, a style change cannot be done together
       with other changes. Therefore a style change is not applied instantly. Call other mapbox
       methods after you've set the style, and add this method as the last one.
    */
    Map & applyMapStyle();

    // controls
    Map & addNavigationControl (CONTROL_POS pos = TOPRIGHT  );
    Map & addGeoLocateControl  (CONTROL_POS pos = TOPLEFT   );
    Map & addAttributionControl(CONTROL_POS pos = BOTTOMLEFT);
    Map & addGeoCoderControl   ();

    // events
    Wt::JSignal<Coordinate> & clicked      () { return clicked_      ; }
    Wt::JSignal<Coordinate> & doubleClicked() { return doubleClicked_; }
    Wt::JSignal<Coordinate> & mouseMoved   ();

    // interactions
    // Should be one of I_DRAGPAN, I_BOXZOOM, ...
    void enableInteraction(const std::string & interaction, bool value);

    // sources
    Map & addSource   (Source * source);
    Map & removeSource(Source * source);

    // layers
    Map & addLayer   (Layer * layer);
    Map & removeLayer(Layer * layer);

  protected:
    virtual void render(Wt::WFlags<Wt::RenderFlag> flags);
    virtual void doGmJavaScript(const std::string & jscode);
    virtual void doOnLoadJavaScript(const std::string & jscode);

    void streamJSListener(const Wt::JSignal<Coordinate> & signal, std::string signalName, Wt::WStringStream & stream);

  private:
    Wt::JSignal<Coordinate> clicked_;
    Wt::JSignal<Coordinate> doubleClicked_;
    Wt::JSignal<Coordinate> * mouseMoved_;

    std::vector<std::string> additions_;
    std::vector<std::string> onLoadAdditions_;
    Coordinate center_;
    std::string mapStyle_;
    bool mapStyleChanging_;
    float zoom_;
    std::string language_;

    std::vector<Layer> layers_;
  };

}