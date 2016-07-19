#pragma once

namespace MapBox {

  enum class LAYERTYPE {
    Background,
    Fill,
    Line,
    Symbol,
    Raster,
    Circle,
  };

  enum class SOURCETYPE {
    Vector,
    Raster,
    GeoJSON,
    Image,
    Video,
  };

  enum class ANCHOR {
    Map,
    Viewport,
  };

  enum class CAP {
    Butt,
    Round,
    Square,
  };

  enum class JOIN {
    Bevel,
    Round,
    Miter,
  };

  enum class PLACEMENT {
    Point,
    Line,
  };

 

  enum class JUSTIFY {
    Left,
    Center,
    Right,
  };

  

  enum class TEXT_ANCHOR {
    Center,
    Left,
    Right,
    Top,
    Bottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
  };

  

  enum class TRANSFORM {
    None,
    UPPERCASE,
    lowercase,
  };

  enum class EVENT {
    WebGlContextLost,
    WebGlContextRestored,
    TouchCancel,
    Click,
    MouseMove,
    TouchMove,
    MouseOut,
    MoveEnd,
    TouchStart,
    Load,
    ContextMenu,
    DblClick,
    MoveStart,
    Render,
    Move,
    Mousedown,
    MouseUp,
    TouchEnd,
    ZoomStart,
    Zoom,
    ZoomEnd,
    BoxZoomEnd,
    BoxZoomStart,
    BoxZoomCancel,
    Rotate,
    RotateEnd,
    RotateStart,
    DragStart,
    Drag,
    DragEnd,
    Pitch,
  };

  enum class CONTROL {
    Navigation,
    GeoLocate,
    Attribution,
    Directions,
    GeoCoder,
  };
}
