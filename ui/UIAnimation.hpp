#pragma once

#include "Managed.hpp"

namespace glider::ui {

class UIAnimation : public Managed {
public:
  virtual void onStart() {
  }
  virtual void onEnd() {
  }
  virtual bool update(int mcsec) = 0;
  virtual bool deleteOnFinish() {
    return true;
  }
};

}  // namespace glider::ui
