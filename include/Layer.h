#pragma once

#include <string>
#include <map>

#include "Source.h"

namespace MapBox {
  enum LAYERTYPE {
    LT_BACKGROUND,
    LT_FILL      ,
    LT_LINE      ,
    LT_SYMBOL    ,
    LT_RASTER    ,
    LT_CIRCLE    ,
  };

  class Map;

  class Layer
  {
  public:
    Layer();

    // layout properties
    Layer & setVisible(bool value); bool visible() const;

    Layer & setSource(Source * source);
    Layer & setZoom  (int min, int max);
    Layer & setFilter(const std::string & value);
    
    LAYERTYPE           type() const { return type_; }
    const std::string & id  () const { return id_  ; }

    std::string render(Map * parent);

    Layer       & setLayout(const std::string & key, const std::string & value);
    Layer       & remLayout(const std::string & key);
    std::string   getLayout(const std::string & key) const;

    Layer       & setPaint(const std::string & key, const std::string & value);
    Layer       & remPaint(const std::string & key); 
    std::string   getPaint(const std::string & key) const;
    

  protected:
    Layer & setType(LAYERTYPE type);

    void addLayoutProperties(std::stringstream & stream) const;
    void addPaintProperties (std::stringstream & stream) const;

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

