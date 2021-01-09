#pragma once

#include "Line.hpp"
#include "Rectangle.hpp"
#include "UIObject.hpp"

namespace glider::ui {

class Slider : public UIObject {
public:
  Slider(float argCurValue = 0.0, float argMinValue = 0.0, float argMaxValue = 1.0);
  float getValue() const {
    return curValue;
  }
  void setValue(float argValue) {
    curValue = argValue;
  }

  void draw();

protected:
  float curValue, minValue, maxValue;
  Rectangle rect;
  Line line;
  bool mouseDown;

  void updateValue(int mx);

  void onMouseButtonDown(const MouseEvent& me);
  void onMouseButtonUp(const MouseEvent& me);
  void onMouseMove(const MouseEvent& me);
};

}  // namespace glider::ui
