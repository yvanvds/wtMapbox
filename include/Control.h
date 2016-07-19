#pragma once

#include <Wt/WCompositeWidget>
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {
  class Map;

  class Control : public Wt::WCompositeWidget {
  public:
    Control(CONTROL type, TEXT_ANCHOR anchor, Wt::WContainerWidget * parent = 0);

    Control & addTo(C Map & map);
    Control & remove();

  protected:
    virtual void render(Wt::WFlags<Wt::RenderFlag> flags);
    virtual void doDelayedJavaScript(const Wt::WString & jscode);
    
  private:
    CONTROL type_;
    TEXT_ANCHOR anchor_;

    std::vector<Wt::WString> additions_;
  };
}