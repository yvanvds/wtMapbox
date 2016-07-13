#include "Layer.h"
#include "Map.h"
#include <sstream>


namespace MapBox {

  int nextLayerID = 0;

  std::string getNextLayerID() {
    std::stringstream stream;
    stream << "maplayer-" << nextLayerID++;
    return stream.str();
  }

  std::string layerToType(LAYERTYPE type) {
    switch (type) {
      case LT_BACKGROUND: return "background";
      case LT_FILL      : return "fill";
      case LT_LINE      : return "line";
      case LT_SYMBOL    : return "symbol";
      case LT_RASTER    : return "raster";
      case LT_CIRCLE    : return "circle";
    }
  }

  Layer::Layer() : id_(getNextLayerID()), source_(nullptr), parent_(nullptr)
  {
    minZoom_ = maxZoom_ = -1; // not used if negative
    
  }

  Layer & Layer::setVisible(bool value) {
    if (value) setLayout("visibility", "'visible'");
    else      setLayout("visibility", "'none'");
    return *this;
  }

  bool Layer::visible() const
  {
    if (getLayout("visibility") == "none") return false;
    return true; // layers are visible by default
  }

  Layer & Layer::setSource(Source * source) {
    source_ = source;
    return *this;
  }

  Layer & Layer::setZoom(int min, int max) {
    minZoom_ = min;
    maxZoom_ = max;
    return *this;
  }

  Layer & Layer::setType(LAYERTYPE type) {
    type_ = type;
    return *this;
  }

  Layer & Layer::setLayout(const std::string & key, const std::string & value)
  {
    if (parent_ != nullptr) {
      // change the current value of this property
      std::stringstream stream;
      stream << "try {\n";
      stream << parent_->jsRef()
        << ".map.setLayoutProperty('"
        << id() << "', '"
        << key << "', " << value << ");\n";
      stream << "} catch(err) {}\n";
      parent_->doJavaScript(stream.str());
    }

    layoutProperties.emplace(key, value);
    return *this;
  }

  std::string Layer::getLayout(const std::string & key) const
  {
    auto it = layoutProperties.find(key);
    if (it != layoutProperties.end()) {
      return it->second;
    }
    return std::string();
  }

  Layer & Layer::remLayout(const std::string & key)
  {
    auto it = layoutProperties.find(key);
    if (it != layoutProperties.end()) {
      layoutProperties.erase(it);
    }
    return *this;
  }

  Layer & Layer::setPaint(const std::string & key, const std::string & value)
  {
    if (parent_ != nullptr) {
      // change the current value of this property
      std::stringstream stream;
      stream << "try {\n";
      stream <<    parent_->jsRef() 
                   << ".map.setPaintProperty('" 
                   << id() << "', '" 
                   << key << "', " << value << ");\n";
      stream << "} catch(err) {}\n";
      parent_->doJavaScript(stream.str());
    }

    // put in container for rendering
    paintProperties.emplace(key, value);
    return *this;
  }

  std::string Layer::getPaint(const std::string & key) const
  {
    auto it = paintProperties.find(key);
    if (it != paintProperties.end()) {
      return it->second;
    }
    return std::string();
  }

  Layer & Layer::remPaint(const std::string & key)
  {
    auto it = paintProperties.find(key);
    if (it != paintProperties.end()) {
      paintProperties.erase(it);
    }
    return *this;
  }

  void Layer::addLayoutProperties(std::stringstream & stream) const
  {
    for (auto it = layoutProperties.begin(); it != layoutProperties.end();) {
      stream << "     '" << it->first << "': ";
      stream << "" << it->second;
      ++it;
      if (it != layoutProperties.end()) {
        stream << ",\n";
      }
      else {
        stream << "\n";
        break;
      }
    }
  }

  void Layer::addPaintProperties(std::stringstream & stream) const
  {
    for (auto it = paintProperties.begin(); it != paintProperties.end();) {
      stream << "     '" << it->first << "': ";
      stream << "" << it->second;
      ++it;
      if (it != paintProperties.end()) {
        stream << ",\n";
      }
      else {
        stream << "\n";
        break;
      }
    }
  }

  Layer & Layer::setFilter(const std::string & value) {
    filter_ = value;
    return *this;
  }

  std::string Layer::render(Map * parent) {
    // once we've set a parent, properties can be changed on the rendered map
    parent_ = parent;

    std::stringstream stream;
    stream
      << "{\n"
      << "  'id': '" << id_ << "',\n"
      << "  'type': '" << layerToType(type_) << "',\n"
      << "  'source': '" << source_->id() << "',\n";

    if (minZoom_ > -1) {
      stream << "  'minzoom': " << minZoom_ << ",\n";
    }

    if (maxZoom_ > -1) {
      stream << "  'maxzoom': " << maxZoom_ << ",\n";
    }

    stream << "  'layout': {\n";
    addLayoutProperties(stream);
    stream << "  },\n";

    stream << "  'paint': {\n";
    addPaintProperties(stream);
    stream << "  }\n";

    if (!filter_.empty()) {
      stream << ",\n";
      stream << "  'filter': " << filter_ << "\n";
    }
    
        
    stream << "}";

    return stream.str();
  }

} // namespace MapBox