#include "Control.h"
#include "Conversions.h"
#include "Map.h"

namespace MapBox {
  Control::Control(CONTROL type, TEXT_ANCHOR anchor, Wt::WContainerWidget * parent)
    : type_(type)
    , anchor_(anchor)
  {
    setImplementation(new Wt::WContainerWidget()); // TODO is this needed?
    if (parent) parent->addWidget(this);
  }

  Control & Control::addTo(C Map & map)
  {
    std::stringstream stream;
    //stream << map.jsRef() << ".map.addControl(" << jsRef() << ".control);";
    stream << jsRef() << ".control.addTo(" << map.jsRef() << ".map);";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  Control & Control::remove()
  {
    std::stringstream stream;
    //stream //<< "try {"
      if (type_ == CONTROL::Directions) {
        stream << jsRef() << ".control._unload();";
      } 
      else {
        stream << jsRef() << ".control.remove();";
      }
      //<< jsRef() << ".control.remove();";
      //<< "} catch(err) {}";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  void Control::render(Wt::WFlags<Wt::RenderFlag> flags)
  {
    Wt::WApplication * app = Wt::WApplication::instance();
    Wt::WString initFunction = app->javaScriptClass() + ".init_control_" + id();

    Wt::WStringStream stream;
    stream
      << "{" << initFunction.toUTF8() << " = function() {"
      << "  var self = " << jsRef() << ";"
      << "  if (!self) {"
      << "    setTimeout(" << initFunction.toUTF8() << ", 0);"
      << "  }";

    switch (type_) {
      case CONTROL::Attribution: stream << " self.control = new mapboxgl.Attribution( {"; break;
      case CONTROL::Directions: stream << " self.control = new mapboxgl.Directions( {"; break;
      case CONTROL::GeoCoder: stream << " self.control = new mapboxgl.Geocoder( {"; break;
      case CONTROL::GeoLocate: stream << " self.control = new mapboxgl.Geolocate( {"; break;
      case CONTROL::Navigation: stream << " self.control = new mapboxgl.Navigation( {"; break;
    }

    stream
      << "    position: " << ToScript(anchor_).toUTF8()
      << "  });";

    for (unsigned int i = 0; i < additions_.size(); i++) {
      stream << additions_[i].toUTF8();
    }
    additions_.clear();

    stream
      << "  setTimeout(function(){ delete " << initFunction.toUTF8() << ";}, 0)};\n"
      << "}\n"
      << initFunction.toUTF8() << "();\n";

    app->doJavaScript(stream.str());
  }

  void Control::doDelayedJavaScript(const Wt::WString & jscode)
  {
    if (isRendered()) {
      doJavaScript(jscode.toUTF8());
    }
    else {
      additions_.push_back(jscode);
    }
  }

}