#include "Popup.h"
#include "Conversions.h"
#include "Map.h"

namespace MapBox {
  
  Popup::Popup(Wt::WContainerWidget * parent, bool closeButton, bool closeOnClick, TEXT_ANCHOR anchor)
    : closeButton_(closeButton)
    , closeOnClick_(closeOnClick)
    , anchor_(anchor)
  {
    setImplementation(new Wt::WContainerWidget());
    if (parent) parent->addWidget(this);
  }

  Popup & Popup::pos(C Coordinate & value)
  {
    std::stringstream stream;
    stream << jsRef() << ".popup.setLngLat(" << ToScript(value) << ");";
    doDelayedJavaScript(stream.str());
    pos_ = value;
    return *this;
  }

  Popup & Popup::setText(C Wt::WString & content)
  {
    std::stringstream stream;
    stream << jsRef() << ".popup.setText(" << Quote(content) << ");";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  Popup & Popup::setHTML(C Wt::WString & content)
  {
    std::stringstream stream;
    stream << jsRef() << ".popup.setHTML(" << Quote(content) << ");";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  Popup & Popup::addTo(C Map & map) {
    std::stringstream stream;
    stream << jsRef() << ".popup.addTo(" << map.jsRef() << ".map);";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  Popup & Popup::remove() {
    std::stringstream stream;
    stream << jsRef() << ".popup.remove();";
    doDelayedJavaScript(stream.str());
    return *this;
  }

  void Popup::render(Wt::WFlags<Wt::RenderFlag> flags) {
    Wt::WApplication * app = Wt::WApplication::instance();
    Wt::WString initFunction = app->javaScriptClass() + ".init_popup_" + id();

    Wt::WStringStream stream;
    stream
      << "{" << initFunction.toUTF8() << " = function() {"
      << "  var self = " << jsRef() << ";"
      << "  if (!self) {"
      << "    setTimeout(" << initFunction.toUTF8() << ", 0);"
      << "  }";

    stream
      << "  self.popup = new mapboxgl.Popup( {"
      << "    closeButton: " << ToScript(closeButton_).toUTF8() << ", "
      << "    closeOnClick: " << ToScript(closeOnClick_).toUTF8() << ", "
      << "    anchor: " << ToScript(anchor_).toUTF8()
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

  void Popup::doDelayedJavaScript(const Wt::WString & jscode) {
    if (isRendered()) {
      doJavaScript(jscode.toUTF8());
    }
    else {
      additions_.push_back(jscode);
    }
  }
}