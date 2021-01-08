#pragma once

#include "Managed.hpp"

namespace glider {

class Drawable : public Managed {
public:
  virtual void draw() = 0;
};

typedef ReferenceTmpl<Drawable> DrawableRef;

}  // namespace glider
