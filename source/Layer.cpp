#include "Layer.h"
#include "Map.h"
#include <sstream>


namespace MapBox {

  int nextLayerID = 0;

  Wt::WString getNextLayerID() {
    std::stringstream stream;
    stream << "maplayer-" << nextLayerID++;
    return stream.str();
  }

  Wt::WString layerToType(LAYERTYPE type) {
    switch (type) {
      case LAYERTYPE::Background: return "background";
      case LAYERTYPE::Fill      : return "fill";
      case LAYERTYPE::Line      : return "line";
      case LAYERTYPE::Symbol    : return "symbol";
      case LAYERTYPE::Raster    : return "raster";
      case LAYERTYPE::Circle    : return "circle";
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

  Layer & Layer::setSourceLayer(C Wt::WString & value) {
    slayer_ = value;
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

  Layer & Layer::setLayout(const Wt::WString & key, const Wt::WString & value)
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

  Wt::WString Layer::getLayout(const Wt::WString & key) const
  {
    auto it = layoutProperties.find(key);
    if (it != layoutProperties.end()) {
      return it->second;
    }
    return Wt::WString();
  }

  Layer & Layer::remLayout(const Wt::WString & key)
  {
    auto it = layoutProperties.find(key);
    if (it != layoutProperties.end()) {
      layoutProperties.erase(it);
    }
    return *this;
  }

  Layer & Layer::setPaint(const Wt::WString & key, const Wt::WString & value)
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

  Wt::WString Layer::getPaint(const Wt::WString & key) const
  {
    auto it = paintProperties.find(key);
    if (it != paintProperties.end()) {
      return it->second;
    }
    return Wt::WString();
  }

  Layer & Layer::remPaint(const Wt::WString & key)
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

  Layer & Layer::setFilter(const Wt::WString & value) {
    filter_ = value;
    return *this;
  }

  Wt::WString Layer::render(Map * parent) {
    // once we've set a parent, properties can be changed on the rendered map
    parent_ = parent;

    std::stringstream stream;
    stream
      << "{\n"
      << "  'id': '" << id_ << "',\n"
      << "  'type': '" << layerToType(type_) << "',\n"
      << "  'source': '" << source_->id() << "',\n";

    if (!slayer_.empty()) {
      stream << "  'source-layer': '" << slayer_ << "',\n";
    }

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