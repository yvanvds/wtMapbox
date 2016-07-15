#pragma once

using namespace Wt;

class Demo : public WContainerWidget {
public:
  virtual void onShow() = 0;
  virtual void onHide() = 0;
};
