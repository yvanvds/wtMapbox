#include "Map.h"
#include "Coordinate.h"
#include "BackgroundLayer.h"
#include "Conversions.h"



namespace MapBox {

  Map::Map(Wt::WContainerWidget * parent)
    : clicked_(this, "click")
    , doubleClicked_(this, "dblclick")
    , mouseMoved_(nullptr)
    , mapStyleChanging_(false)
  {
    setImplementation(new Wt::WContainerWidget());
    if (parent) parent->addWidget(this);
    this->addCssRule("#" + id(), "position:absolute; top:0; bottom:0; width:100%;");

    Wt::WApplication * app = Wt::WApplication::instance();

   
    const std::string mburi = "https://api.mapbox.com/mapbox-gl-js/v0.18.0/mapbox-gl.js";
    app->require(mburi, "mapbox");
    app->useStyleSheet(Wt::WCssStyleSheet(Wt::WLink("https://api.mapbox.com/mapbox-gl-js/v0.18.0/mapbox-gl.css")));

    const std::string mbguri = "https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-geocoder/v1.0.0/mapbox-gl-geocoder.js";
    app->require(mbguri, "mapboxgeocoder");
    app->useStyleSheet(Wt::WCssStyleSheet(Wt::WLink("https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-geocoder/v1.0.0/mapbox-gl-geocoder.css")));

    const std::string supported = "https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-supported/v0.0.1/mapbox-gl-supported.js";
    app->require(supported, "mapboxsupported");
  }


  Map::~Map()
  {
  }

  void Map::render(Wt::WFlags<Wt::RenderFlag> flags) {
    if (flags & Wt::RenderFull) {
      Wt::WApplication * app = Wt::WApplication::instance();
      std::string mapboxKey;
      Wt::WApplication::readConfigurationProperty("mapbox_api_key", mapboxKey);
      
      std::string initFunction = app->javaScriptClass() + ".init_mapbox_" + id();

      Wt::WStringStream stream;
      stream
        << "{ " << initFunction << " = function() {\n"
        << "  var self = " << jsRef() << ";\n"
        << "  if (!self) {\n"
        << "    setTimeout(" << initFunction << ", 0);\n"
        << "  }\n";

      stream
        << "  mapboxgl.accessToken = '" << mapboxKey << "';\n"
        << "  if (!mapboxgl.supported()) {\n"
        << "    alert('Your browser does not support Mapbox GL');\n"
        << "  } else {\n"
        << "    map = new mapboxgl.Map({\n"
        << "      container: self,\n"
        << "      style: 'mapbox://styles/mapbox/streets-v9'\n"
        << "    });\n"
        << "  }\n";

      stream
        << "  self.map = map;\n";

      // event handling
      streamJSListener(clicked_, "click", stream);
      streamJSListener(doubleClicked_, "dblclick", stream);
      if (mouseMoved_) {
        streamJSListener(*mouseMoved_, "mousemove", stream);
      }

      // additional things
      for (unsigned int i = 0; i < additions_.size(); i++) {
        stream << additions_[i];
      }
      additions_.clear();

      // additional things which has to be in the on load function
      if (onLoadAdditions_.size()) {
        stream << "map.on('load', function() {\n";
        for (unsigned int i = 0; i < onLoadAdditions_.size(); i++) {
          stream << onLoadAdditions_[i];
        }
        onLoadAdditions_.clear();
        stream << "});\n";
      }

      stream
        << "  setTimeout(function(){ delete " << initFunction << ";}, 0)};\n"
        << "}\n"
        << initFunction << "();\n";

      app->doJavaScript(stream.str());
    }

    Wt::WCompositeWidget::render(flags);
  }

  void Map::doGmJavaScript(const std::string & jscode) {
    if (isRendered()) {
      if(!mapStyleChanging_) doJavaScript(jscode);
      else additions_.push_back(jscode);
    }
    else {
      additions_.push_back(jscode);
    }
  }

  void Map::doOnLoadJavaScript(const std::string & jscode) {
    if (isRendered()) {
      if (!mapStyleChanging_) doJavaScript(jscode);
      else additions_.push_back(jscode);
    }
    else {
      onLoadAdditions_.push_back(jscode);
    }
  }

  void Map::setZoom(int level) {
    std::stringstream stream;
    stream << jsRef() << ".map.setZoom(" << level << ");\n";
    doGmJavaScript(stream.str());
    zoom_ = level;
  }

  void Map::resize() {
    std::stringstream stream;
    stream << jsRef() << ".map.resize();\n";
    doGmJavaScript(stream.str());
  }

  void Map::setCenter(const Coordinate & coordinate) {
    std::stringstream stream;
    stream
      << jsRef() + ".map.setCenter(";
    Coordinate::write(stream, coordinate);
    stream
      << ");\n";
    doGmJavaScript(stream.str());
    center_ = coordinate;
  }

  void Map::setMapStyle(const std::string & style, bool waitForApply) {
    if (isRendered() && waitForApply) {
      mapStyleChanging_ = true;
    }
    else {
      doGmJavaScript(jsRef() + ".map.setStyle('" + style + "');\n");
    }   
    mapStyle_ = style;
  }

  void Map::applyMapStyle() {
    doJavaScript(jsRef() + ".map.setStyle('" + mapStyle_ + "');\n");
    
    if (additions_.size()) {
      std::stringstream stream;
      stream << "map.style.on('load', function() {\n";
      for (unsigned int i = 0; i < additions_.size(); i++) {
        stream << additions_[i];
      }
      additions_.clear();
      stream << "});\n";
      doJavaScript(stream.str());
    }
    mapStyleChanging_ = false;
  }

  void Map::easeTo(const Coordinate & destination, int zoom, int duration) {
    std::stringstream stream;
    stream << jsRef() + ".map.easeTo({ center: ";
    Coordinate::write(stream, destination);
    center_ = destination;
    if (zoom > -1) {
      stream << ", zoom: " << zoom;
      zoom_ = zoom;
    }
    if (duration > -1) {
      stream << ", duration: " << duration;
    }
    stream << "});\n";

    doGmJavaScript(stream.str());
  }

  void Map::flyTo(const Coordinate & destination, int zoom, float curve, float speed) {
    std::stringstream stream;
    stream << jsRef() + ".map.flyTo({ center: ";
    Coordinate::write(stream, destination);
    center_ = destination;
    if (zoom > -1) {
      stream << ", zoom: " << zoom;
      zoom_ = zoom;
    }
    stream << ", curve: " << curve;
    stream << ", speed: " << speed;
    stream << "});\n";

    doGmJavaScript(stream.str());
  }

  void Map::fitBounds(C Bounds & bounds, bool linear, int padding, int maxZoom)
  {
    std::stringstream stream;
    stream << jsRef() + ".map.fitBounds(["
      << ToScript(bounds.leftDown) << ", "
      << ToScript(bounds.rightUp) << "]";

    if (linear == true || padding != 0 || maxZoom != -1) {
      stream << ", { ";
      bool isFirst = true;
      
      if (linear == true) {
        stream << "linear: true";
        isFirst = false;
      }

      if (padding != 0) {
        if (!isFirst) stream << ", ";
        stream << "padding: " << padding;
        isFirst = false;
      }

      if (maxZoom != -1) {
        if (!isFirst) stream << ", ";
        stream << "maxZoom: " << maxZoom;
      }

      stream << "}";
    }

    stream << ");";

    doGmJavaScript(stream.str());
  }

  std::string getControlPos(CONTROL_POS pos) {
    switch (pos) {
      case TOPRIGHT   : return "top-right"   ;
      case TOPLEFT    : return "top-left"    ;
      case BOTTOMRIGHT: return "bottom-right";
      case BOTTOMLEFT : return "bottom-left" ;
    }
  }

  void Map::addNavigationControl(CONTROL_POS pos) {
    std::stringstream stream;
    stream << jsRef() + ".map.addControl(new mapboxgl.Navigation());\n";
    doGmJavaScript(stream.str());
  }

  void Map::addGeoLocateControl(CONTROL_POS pos) {
    std::stringstream stream;
    stream << jsRef() + ".map.addControl(new mapboxgl.Geolocate({ position: '";
    stream << getControlPos(pos);
    stream << "' }));\n";
    doGmJavaScript(stream.str());
  }

  void Map::addAttributionControl(CONTROL_POS pos) {
    std::stringstream stream;
    stream << jsRef() + ".map.addControl(new mapboxgl.Attribution({ position: '";
    stream << getControlPos(pos);
    stream << "' }));\n";
    doGmJavaScript(stream.str());
  }

  void Map::addGeoCoderControl() {
    std::stringstream stream;
    stream << jsRef() + ".map.addControl(new mapboxgl.Geocoder());\n";
    doGmJavaScript(stream.str());

  }

  Wt::JSignal<Coordinate> & Map::mouseMoved() {
    if (!mouseMoved_) {
      mouseMoved_ = new Wt::JSignal<Coordinate>(this, "mousemove");
    }
    return *mouseMoved_;
  }

  void Map::streamJSListener(const Wt::JSignal<Coordinate> & signal, std::string signalName, Wt::WStringStream & stream) {
    stream
      << "map.on('" << signalName << "', function (e) {"
      << signal.createCall("e.lngLat.lat +' '+ e.lngLat.lng") << ";"
      << "});\n";
  }

  void Map::enableInteraction(const std::string & interaction, bool value) {
    std::stringstream stream;
    if (value) stream << jsRef() + ".map['" << interaction << "'].enable();";
    else       stream << jsRef() + ".map['" << interaction << "'].disable();";

    doGmJavaScript(stream.str());
  }

  void Map::addSource(Source * source) {
    std::stringstream stream;
    stream << jsRef() + ".map.addSource(";
    stream << source->render();
    stream << ");\n";
    doOnLoadJavaScript(stream.str());
  }

  void Map::removeSource(Source * source)
  {
    std::stringstream stream;
    stream << "try {\n";
    stream <<   jsRef() + ".map.removeSource('";
    stream <<   source->id();
    stream <<   "');\n";
    stream << "} catch(err) {}\n"; // error when the source does not exist. This can be ignored.
    doOnLoadJavaScript(stream.str());
  }

  void Map::addLayer(Layer * layer) {
    std::stringstream stream;
    stream << jsRef() + ".map.addLayer(\n";
    stream << layer->render(this);
    stream << ");\n";
    doOnLoadJavaScript(stream.str());
  }

  void Map::removeLayer(Layer * layer)
  {
    std::stringstream stream;
    stream << "try {\n";
    stream <<   jsRef() + ".map.removeLayer('";
    stream <<   layer->id();
    stream <<   "');\n";
    stream << "} catch(err) {}\n"; // error when the layer does not exist. This can be ignored.
    doOnLoadJavaScript(stream.str());
  }

} // namespace MapBox