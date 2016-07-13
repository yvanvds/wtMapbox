#pragma once

#include <vector>
#include <string>

#include "Coordinate.h"
#include "Layer.h"

namespace MapBox {

  // predefined mapbox styles
  const std::string MAPSTYLE_STREETS = "mapbox://styles/mapbox/streets-v9";
  const std::string MAPSTYLE_OUTDOORS = "mapbox://styles/mapbox/outdoors-v9";
  const std::string MAPSTYLE_LIGHT = "mapbox://styles/mapbox/light-v9";
  const std::string MAPSTYLE_DARK = "mapbox://styles/mapbox/dark-v9";
  const std::string MAPSTYLE_SATELLITE = "mapbox://styles/mapbox/satellite-v9";
  const std::string MAPSTYLE_SATELLITE_STREETS = "mapbox://styles/mapbox/satellite-streets-v9";

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

    /* Set a map location */
    void setCenter(const Coordinate & coordinate);
    const Coordinate & center() { return center_; }

    /* Set a map zoom */
    void setZoom(int level);
    int zoom() { return zoom_; }

    void resize();

    void easeTo(const Coordinate & destination, int zoom = -1, int duration = -1);
    void flyTo(const Coordinate & destination, int zoom = -1, float curve = 1.42, float speed = 1.2);

    /* Replaces the map's style object with a new value. This is an URL string. Refer
       to mapbox api for syntax or use one of the predefined styles above.
       */
    void setMapStyle(const std::string & style);
    const std::string & mapStyle() { return mapStyle_; }

    // controls
    void addNavigationControl (CONTROL_POS pos = TOPRIGHT  );
    void addGeoLocateControl  (CONTROL_POS pos = TOPLEFT   );
    void addAttributionControl(CONTROL_POS pos = BOTTOMLEFT);
    void addGeoCoderControl();

    // events
    Wt::JSignal<Coordinate> & clicked() { return clicked_; }
    Wt::JSignal<Coordinate> & doubleClicked() { return doubleClicked_; }
    Wt::JSignal<Coordinate> & mouseMoved();

    // interactions
    // Should be one of I_DRAGPAN, I_BOXZOOM, ...
    void enableInteraction(const std::string & interaction, bool value);

    // sources
    void addSource(Source * source);
    void removeSource(Source * source);

    // layers
    void addLayer(Layer * layer);
    void removeLayer(Layer * layer);

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
    int zoom_;

    std::vector<Layer> layers_;
  };

}