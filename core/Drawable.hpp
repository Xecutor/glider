#pragma once

#include "Managed.hpp"

namespace glider {

class Drawable : public Managed {
public:
  using Ref = ReferenceTmpl<Drawable>;
  virtual void draw() = 0;
};

}  // namespace glider
