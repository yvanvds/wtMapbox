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
    Layer & setVisible(bool value); bool visible() C;

    Layer & setSource(Source * source);
    Layer & setZoom  (int min, int max);
    Layer & setFilter(const std::string & value);
    
      LAYERTYPE     type() C { return type_; }
    C std::string & id  () C { return id_  ; }

    std::string render(Map * parent);

    Layer       & setLayout(C std::string & key, C std::string & value);
    Layer       & remLayout(C std::string & key);
    std::string   getLayout(C std::string & key) C;

    Layer       & setPaint(C std::string & key, C std::string & value);
    Layer       & remPaint(C std::string & key); 
    std::string   getPaint(C std::string & key) C;
    

  protected:
    Layer & setType(LAYERTYPE type);

    void addLayoutProperties(std::stringstream & stream) C;
    void addPaintProperties (std::stringstream & stream) C;

  private:
    std::string   id_    ;
    Source      * source_;
    LAYERTYPE     type_  ;
    std::string   filter_;
    Map         * parent_;

    int minZoom_;
    int maxZoom_;

    std::map<std::string, std::string> layoutProperties;
    std::map<std::string, std::string> paintProperties ;
  };

} // namespace MapBox

