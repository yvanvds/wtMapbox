#pragma once

#include "Coordinate.h"
#include "Definitions.h"
#include "Enumerations.h"
#include <Wt/WCompositeWidget>

namespace MapBox {

  class Map;

  class Popup : public Wt::WCompositeWidget
  {
  public:
    Popup(Wt::WContainerWidget * parent = 0, bool closeButton = true, bool closeOnClick = true, TEXT_ANCHOR anchor = TEXT_ANCHOR::Bottom);

    Popup & pos(C Coordinate & value); C Coordinate & pos() C { return pos_; }
    
    Popup & setText(C Wt::WString & content);
    Popup & setHTML(C Wt::WString & content);
    Popup & setDomContent(); // TODO

    Popup & addTo(C Map & map);
    Popup & remove();

  protected:
    virtual void render(Wt::WFlags<Wt::RenderFlag> flags);
    virtual void doDelayedJavaScript(const Wt::WString & jscode);

  private:
    bool closeButton_;
    bool closeOnClick_;
    TEXT_ANCHOR anchor_;
    Coordinate pos_;

    std::vector<Wt::WString> additions_;

  };

}