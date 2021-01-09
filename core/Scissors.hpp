#pragma once

#include "Drawable.hpp"
#include "Utility.hpp"

namespace glider {

class Scissors : public Drawable {
public:
  Scissors() : obj(0) {
  }
  Scissors(const Rect& argRect) : rect(argRect), obj(0) {
  }

  void assignObj(Drawable* argObj) {
    obj = argObj;
  }

  void setRect(const Rect& argRect) {
    rect = argRect;
  }

  const Rect& getRect() const {
    return rect;
  }

  void draw(Drawable* argObj);
  void draw();

protected:
  Rect rect;
  Drawable::Ref obj;
};

}  // namespace glider
