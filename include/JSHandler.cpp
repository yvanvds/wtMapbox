#include "JSHandler.h"
#include "Conversions.h"

namespace MapBox {

  int nextJSHandlerID = 0;

  Wt::WString getNextJSHandlerID() {
    std::stringstream stream;
    stream << "jshandler-" << nextJSHandlerID++;
    return stream.str();
  }

  JSHandler::JSHandler()
    : id_(getNextJSHandlerID())
  {}

  JSHandler & JSHandler::trigger(EVENT event)
  {
    event_ = event;
    return *this;
  }

  JSHandler & JSHandler::code(C Wt::WString & content)
  {
    content_ = content;
    return *this;
  }

}