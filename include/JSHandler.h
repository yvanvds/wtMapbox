#pragma once
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {

  class JSHandler {
  public:
    JSHandler();

    JSHandler & trigger(      EVENT     event  );       EVENT     trigger() C { return event_  ; }
    JSHandler & code   (C Wt::WString & content); C Wt::WString & code   () C { return content_; }

    C Wt::WString & id() C { return id_; }

  private:
    EVENT       event_  ;
    Wt::WString content_;
    Wt::WString id_     ;
  };

}