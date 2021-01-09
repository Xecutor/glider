#pragma once

#include "Drawable.hpp"
#include "Utility.hpp"

namespace glider {

class Rectangle : public Drawable {
public:
  using Ref = ReferenceTmpl<Rectangle>;

  Rectangle() : fill(true) {
  }
  Rectangle(const Rect& argRect, const Color& argColor, bool argFill = true)
      : pos(argRect.pos), size(argRect.size), clr(argColor), fill(argFill) {
  }
  void setColor(const Color& argColor) {
    clr = argColor;
  }
  void setPosition(const Pos& argPos) {
    pos = argPos;
  }
  void setSize(const Pos& argSize) {
    size = argSize;
  }
  const Pos& getPosition() const {
    return pos;
  }
  const Pos& getSize() const {
    return size;
  }
  const Rect getRect() const {
    return Rect(pos, size);
  }
  void setFill(bool argFill) {
    fill = argFill;
  }
  void draw();

protected:
  Pos pos;
  Pos size;
  Color clr;
  bool fill;
};

}  // namespace glider
