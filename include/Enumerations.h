#pragma once

namespace MapBox {
  enum class ANCHOR {
    Map,
    Viewport,
  };

  std::string AnchorToString(ANCHOR value);

  enum class CAP {
    Butt,
    Round,
    Square,
  };

  std::string CapToString(CAP value);

  enum class JOIN {
    Bevel,
    Round,
    Miter,
  };

  std::string JoinToString(JOIN value);
}
