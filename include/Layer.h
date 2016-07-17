#pragma once

#include <string>
#include <map>

#include "Source.h"
#include "Enumerations.h"
#include "Definitions.h"

namespace MapBox {

  class Map;

  class Layer
  {
  public:
    Layer();

    // layout properties
    Layer & visible(bool value); bool visible() C;

    Layer & set(Source * source);
    Layer & sourceLayer(C Wt::WString & value);
    Layer & zoom  (int min, int max);
    Layer & filter(const Wt::WString & value);
    
      LAYERTYPE     type() C { return type_; }
    C Wt::WString & id  () C { return id_  ; }

    Wt::WString render(Map * parent);

    // you could use these to set properties which are not implemented
    Layer       & setLayout(C Wt::WString & key, C Wt::WString & value);
    Layer       & remLayout(C Wt::WString & key);
    Wt::WString   getLayout(C Wt::WString & key) C;

    Layer       & setPaint(C Wt::WString & key, C Wt::WString & value);
    Layer       & remPaint(C Wt::WString & key); 
    Wt::WString   getPaint(C Wt::WString & key) C;
    

  protected:
    Layer & type(LAYERTYPE type);

    void addLayoutProperties(std::stringstream & stream) C;
    void addPaintProperties (std::stringstream & stream) C;

  private:
    Wt::WString   id_    ;
    Source      * source_;
    LAYERTYPE     type_  ;
    Wt::WString   filter_;
    Wt::WString   slayer_;
    Map         * parent_;

    int minZoom_;
    int maxZoom_;

    std::map<Wt::WString, Wt::WString> layoutProperties;
    std::map<Wt::WString, Wt::WString> paintProperties ;
  };

} // namespace MapBox

