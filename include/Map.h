#pragma once

#include <vector>
#include <string>

#include "Coordinate.h"
#include "Layer.h"
#include "JSHandler.h"

namespace MapBox {

  // predefined mapbox styles
  namespace MAPSTYLE {
    const Wt::WString Streets = "mapbox://styles/mapbox/streets-v9";
    const Wt::WString Outdoors = "mapbox://styles/mapbox/outdoors-v9";
    const Wt::WString Light = "mapbox://styles/mapbox/light-v9";
    const Wt::WString Dark = "mapbox://styles/mapbox/dark-v9";
    const Wt::WString Satellite = "mapbox://styles/mapbox/satellite-v9";
    const Wt::WString SatelliteStreets = "mapbox://styles/mapbox/satellite-streets-v9";
  }

  // interactions
  const Wt::WString I_SCROLLZOOM = "scrollZoom";
  const Wt::WString I_BOXZOOM = "boxZoom";
  const Wt::WString I_DRAGROTATE = "dragRotate";
  const Wt::WString I_DRAGPAN = "dragPan";
  const Wt::WString I_KEYBOARD = "keyboard";
  const Wt::WString I_DOUBLECLICKZOOM = "doubleClickZoom";
  const Wt::WString I_TOUCHZOOMROTATE = "touchZoomRotate";

  enum CONTROL_POS {
    TOPRIGHT,
    TOPLEFT,
    BOTTOMRIGHT,
    BOTTOMLEFT,
  };


  class Map : public Wt::WCompositeWidget
  {
  public:

    Map(Wt::WContainerWidget * parent = 0, bool withDirections = false);
    virtual ~Map();

    /* Set a map zoom */
    Map & zoom(float level);   float zoom() C { return zoom_; }
    /* Sets the maps' bearing, measured in degrees counter-clokwise from north.*/
    Map & bearing(int degrees); int bearing() C { return bearing_; }
    /* Sets the maps' pitch (tilt) measured in degrees away from the plane of the screen (0-60) */
    Map & pitch(int degrees); int pitch() C { return pitch_; }

    Map & resize();

    /* set a language (2 letter language code) */
    Map & language(C Wt::WString & code); C Wt::WString & language() C { return language_; }

    /* Set a map location */
    Map & center   (C Coordinate & coordinate); C Coordinate & center() C { return center_; }
    Map & easeTo   (C Coordinate & destination, int  zoom   = -1   , int   duration = -1                        );
    Map & flyTo    (C Coordinate & destination, int  zoom   = -1   , float curve    = 1.42, float speed   =  1.2);
    Map & fitBounds(C Bounds     & bounds     , bool linear = false, int   padding  = 0   , int   maxZoom = -1  );


    /* Replaces the map's style object with a new value. This is an URL string. Refer
       to mapbox api for syntax or use one of the predefined styles above.
       */
    Map & setMapStyle(const Wt::WString & style, bool waitForApply = false); C Wt::WString & mapStyle() C { return mapStyle_; }

    /* Once the map is rendered, a style change cannot be done together
       with other changes. Therefore a style change is not applied instantly. Call other mapbox
       methods after you've set the style, and add this method as the last one.
    */
    Map & applyMapStyle();

    // events
    Wt::JSignal<Coordinate> & clicked      () { return clicked_      ; }
    Wt::JSignal<Coordinate> & doubleClicked() { return doubleClicked_; }
    Wt::JSignal<Coordinate> & mouseMoved   ();

    // 
    /* 
    A signal to retrieve a feature from the specified layer on mouse click.

    This signal must be explicitly enabled on the client side.
    It is also a good idea to disable the signal when you're done, so
    to minimize traffic.

    At any rate it should be disabled before the mentioned layer is removed.
    */
    Wt::JSignal<Wt::WString> & clickedFeature(C Wt::WString & layers);
    
    Map & enableClickedFeature(bool enable);

    // interactions
    // Should be one of I_DRAGPAN, I_BOXZOOM, ...
    void enableInteraction(const Wt::WString & interaction, bool value);

    // client side event handler
    Map & add(C JSHandler & handler);
    Map & rem(C JSHandler & handler);

    // sources
    Map & add(Source * source);
    Map & rem(Source * source);

    // Add a layer to the map. The new layer will be displayed on top of all existing layers, unless a layer name is specified as second argument.
    Map & add(Layer * layer, C Wt::WString & before = Wt::WString());
    Map & rem(Layer * layer);

    // modify properties
    Map & setPaintProperty(C Wt::WString & layer, C Wt::WString & _property, C Wt::WString & value);

  protected:
    virtual void render(Wt::WFlags<Wt::RenderFlag> flags);
    virtual void doGmJavaScript(const Wt::WString & jscode);
    virtual void doOnLoadJavaScript(const Wt::WString & jscode);

    void streamJSListener(const Wt::JSignal<Coordinate> & signal, Wt::WString signalName, Wt::WStringStream & stream);

  private:
    Wt::JSignal<Coordinate> clicked_;
    Wt::JSignal<Coordinate> doubleClicked_;
    Wt::JSignal<Coordinate> * mouseMoved_;
    Wt::JSignal<Wt::WString> * clickedFeature_;

    std::vector<Wt::WString> additions_;
    std::vector<Wt::WString> onLoadAdditions_;
    Coordinate center_;
    Wt::WString mapStyle_;
    bool mapStyleChanging_;
    float zoom_;
    int pitch_;
    int bearing_;
    Wt::WString language_;
    bool directionsEnabled_;

    //std::vector<Layer> layers_;
  };

}