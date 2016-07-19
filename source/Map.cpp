#include "Map.h"
#include "Coordinate.h"
#include "BackgroundLayer.h"
#include "Conversions.h"
#include "GeoJSON.h"


namespace MapBox {

  Map::Map(Wt::WContainerWidget * parent, bool withDirections)
    : clicked_(this, "click")
    , doubleClicked_(this, "dblclick")
    , mouseMoved_(nullptr)
    , mapStyleChanging_(false)
    , pitch_(0)
    , bearing_(0)
    , language_("en")
    , directionsEnabled_(withDirections)
  {
    setImplementation(new Wt::WContainerWidget());
    if (parent) parent->addWidget(this);
    this->addCssRule("#" + id(), "position:absolute; top:0; bottom:0; width:100%;");

    Wt::WApplication * app = Wt::WApplication::instance();

   
    C std::string mburi = "https://api.mapbox.com/mapbox-gl-js/v0.18.0/mapbox-gl.js";
    app->require(mburi, "mapbox");
    app->useStyleSheet(Wt::WCssStyleSheet(Wt::WLink("https://api.mapbox.com/mapbox-gl-js/v0.18.0/mapbox-gl.css")));

    C std::string mbguri = "https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-geocoder/v1.0.0/mapbox-gl-geocoder.js";
    app->require(mbguri, "mapboxgeocoder");
    app->useStyleSheet(Wt::WCssStyleSheet(Wt::WLink("https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-geocoder/v1.0.0/mapbox-gl-geocoder.css")));

    C std::string supported = "https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-supported/v0.0.1/mapbox-gl-supported.js";
    app->require(supported, "mapboxsupported");

    C std::string diruri = "https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-directions/v2.1.0/mapbox-gl-directions.js";
    app->require(diruri, "mapboxdirections");
    app->useStyleSheet(Wt::WCssStyleSheet(Wt::WLink("https://api.mapbox.com/mapbox-gl-js/plugins/mapbox-gl-directions/v2.1.0/mapbox-gl-directions.css")));


  }


  Map::~Map()
  {
  }

  void Map::render(Wt::WFlags<Wt::RenderFlag> flags) {
    if (flags & Wt::RenderFull) {
      Wt::WApplication * app = Wt::WApplication::instance();
      std::string mapboxKey;
      Wt::WApplication::readConfigurationProperty("mapbox_api_key", mapboxKey);
      
      Wt::WString initFunction = app->javaScriptClass() + ".init_mapbox_" + id();

      Wt::WStringStream stream;
      stream
        << "{ " << initFunction.toUTF8() << " = function() {\n"
        << "  var self = " << jsRef() << ";\n"
        << "  if (!self) {\n"
        << "    setTimeout(" << initFunction.toUTF8() << ", 0);\n"
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
        stream << additions_[i].toUTF8();
      }
      additions_.clear();

      // additional things which has to be in the on load function
      if (onLoadAdditions_.size()) {
        stream << "map.on('load', function() {\n";
        for (unsigned int i = 0; i < onLoadAdditions_.size(); i++) {
          stream << onLoadAdditions_[i].toUTF8();
        }
        onLoadAdditions_.clear();
        stream << "});\n";
      }

      stream
        << "  setTimeout(function(){ delete " << initFunction.toUTF8() << ";}, 0)};\n"
        << "}\n"
        << initFunction.toUTF8() << "();\n";

      app->doJavaScript(stream.str());
    }

    Wt::WCompositeWidget::render(flags);
  }

  void Map::doGmJavaScript(const Wt::WString & jscode) {
    if (isRendered()) {
      if(!mapStyleChanging_) doJavaScript(jscode.toUTF8());
      else additions_.push_back(jscode);
    }
    else {
      additions_.push_back(jscode);
    }
  }

  void Map::doOnLoadJavaScript(const Wt::WString & jscode) {
    if (isRendered()) {
      if (!mapStyleChanging_) doJavaScript(jscode.toUTF8());
      else additions_.push_back(jscode);
    }
    else {
      onLoadAdditions_.push_back(jscode);
    }
  }

  Map & Map::zoom(float level) {
    std::stringstream stream;
    stream << jsRef() << ".map.setZoom(" << level << ");\n";
    doGmJavaScript(stream.str());
    zoom_ = level;
    return *this;
  }

  Map & Map::bearing(int degrees) {
    std::stringstream stream;
    stream << jsRef() << ".map.setBearing(" << degrees << ");";
    doGmJavaScript(stream.str());
    bearing_ = degrees;
    return *this;
  }

  Map & Map::pitch(int degrees) {
    std::stringstream stream;
    stream << jsRef() << ".map.setPitch(" << degrees << ");";
    doGmJavaScript(stream.str());
    pitch_ = degrees;
    return *this;
  }

  Map & Map::resize() {
    std::stringstream stream;
    stream << jsRef() << ".map.resize();\n";
    doGmJavaScript(stream.str());
    return *this;
  }

  Map & Map::center(const Coordinate & coordinate) {
    std::stringstream stream;
    stream
      << jsRef() + ".map.setCenter(";
    Coordinate::write(stream, coordinate);
    stream
      << ");\n";
    doGmJavaScript(stream.str());
    center_ = coordinate;
    return *this;
  }

  Map & Map::setMapStyle(const Wt::WString & style, bool waitForApply) {
    if (isRendered() && waitForApply) {
      mapStyleChanging_ = true;
    }
    else {
      doGmJavaScript(jsRef() + ".map.setStyle('" + style + "');\n");
    }   
    mapStyle_ = style;
    return *this;
  }

  Map & Map::applyMapStyle() {
    doJavaScript(jsRef() + ".map.setStyle('" + mapStyle_.toUTF8() + "');\n");
    
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
    return *this;
  }

  Map & Map::easeTo(const Coordinate & destination, int zoom, int duration) {
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
    return *this;
  }

  Map & Map::flyTo(const Coordinate & destination, int zoom, float curve, float speed) {
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
    return *this;
  }

  Map & Map::fitBounds(C Bounds & bounds, bool linear, int padding, int maxZoom)
  {
    std::stringstream stream;
    stream << jsRef() + ".map.fitBounds(["
      << ToScript(bounds.min) << ", "
      << ToScript(bounds.max) << "]";

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
    return *this;
  }

  Map & Map::add(C JSHandler & handler) {
    std::stringstream stream;
    stream << jsRef() << "." << handler.id().toUTF8() << " = " << handler.code().toUTF8() << ";";
    stream << jsRef() << ".map.on(" << ToScript(handler.trigger()) << ", "
      << jsRef() << "." << handler.id().toUTF8() << ");";
    doGmJavaScript(stream.str());
    return *this;
  }

  Map & Map::rem(C JSHandler & handler) {
    std::stringstream stream;
    stream << jsRef() << ".map.off(" << ToScript(handler.trigger()) << ", "
      << jsRef() << "." << handler.id().toUTF8() << ");";
    doGmJavaScript(stream.str());
    return *this;
  }

  Wt::JSignal<Coordinate> & Map::mouseMoved() {
    if (!mouseMoved_) {
      mouseMoved_ = new Wt::JSignal<Coordinate>(this, "mousemove");
    }
    return *mouseMoved_;
  }

  Wt::JSignal<Wt::WString> & Map::clickedFeature(C Wt::WString & layers) {
    if (!clickedFeature_) {
      clickedFeature_ = new Wt::JSignal<Wt::WString>(this, "featureclick");
    }
    
    // add javascript code
    std::stringstream stream;
    stream << jsRef() << ".clickedFeature = function(e) {"
      << "var features = " << jsRef() << ".map.queryRenderedFeatures(e.point, {"
      << "layers: [" + Quote(layers.toUTF8()) + "]"
      << "});"
      << "if(!features.length) { return; }"
      << clickedFeature_->createCall("JSON.stringify(features[0])") << ";"
      << "};";
    doOnLoadJavaScript(stream.str());

    return *clickedFeature_;
  }

  Map & Map::enableClickedFeature(bool enable) {
    std::stringstream stream;
    if (enable) {
      stream << jsRef() << ".map.on('click', " << jsRef() << ".clickedFeature);";
    }
    else {
      stream << jsRef() << ".map.off('click', " << jsRef() << ".clickedFeature);";
    }
    doOnLoadJavaScript(stream.str());
    return *this;
  }

  void Map::streamJSListener(const Wt::JSignal<Coordinate> & signal, Wt::WString signalName, Wt::WStringStream & stream) {
    stream
      << "map.on('" << signalName.toUTF8() << "', function (e) {"
      << signal.createCall("e.lngLat.lat +' '+ e.lngLat.lng") << ";"
      << "});\n";
  }

  void Map::enableInteraction(const Wt::WString & interaction, bool value) {
    std::stringstream stream;
    if (value) stream << jsRef() + ".map['" << interaction << "'].enable();";
    else       stream << jsRef() + ".map['" << interaction << "'].disable();";

    doGmJavaScript(stream.str());
  }

  Map & Map::add(Source * source) {
    std::stringstream stream;
    stream << jsRef() + ".map.addSource(";
    stream << source->render(this);
    stream << ");\n";
    doOnLoadJavaScript(stream.str());
    return *this;
  }

  Map & Map::rem(Source * source)
  {
    std::stringstream stream;
    stream << "try {\n";
    stream <<   jsRef() + ".map.removeSource('";
    stream <<   source->id();
    stream <<   "');\n";
    stream << "} catch(err) {}\n"; // error when the source does not exist. This can be ignored.
    doOnLoadJavaScript(stream.str());
    return *this;
  }

  Map & Map::add(Layer * layer, C Wt::WString & before) {
    std::stringstream stream;
    stream << jsRef() + ".map.addLayer(\n";
    stream << layer->render(this);
    if (!before.empty()) {
      stream << ", '" << before << "'";
    }
    stream << ");\n";
    doOnLoadJavaScript(stream.str());
    return *this;
  }

  Map & Map::rem(Layer * layer)
  {
    std::stringstream stream;
    stream << "try {\n";
    stream <<   jsRef() + ".map.removeLayer('";
    stream <<   layer->id();
    stream <<   "');\n";
    stream << "} catch(err) {}\n"; // error when the layer does not exist. This can be ignored.
    doOnLoadJavaScript(stream.str());
    return *this;
  }

  Map & Map::setPaintProperty(C Wt::WString & layer, C Wt::WString & _property, C Wt::WString & value) {
    std::stringstream stream;
    stream << jsRef() + ".map.setPaintProperty('"
      << layer << "', '" << _property << "', '"
      << value << "');";
    doGmJavaScript(stream.str());
    Wt::log(stream.str());
    return *this;
  }


  Map & Map::language(C Wt::WString & code)
  {
    language_ = code;
    std::stringstream stream;
    // todo: can't find any documentation about supported languages or labels
    stream << jsRef() + ".map.setLayoutProperty('country-label-lg', 'text-field', '{name_" << code << "}');";
    doGmJavaScript(stream.str());   
    return *this;
  }

} // namespace MapBox