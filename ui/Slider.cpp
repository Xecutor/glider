#include "Slider.hpp"

#include "GLState.hpp"
#include "UIRoot.hpp"

namespace glider {
namespace ui {

Slider::Slider(float argCurValue, float argMinValue, float argMaxValue)
    : curValue(argCurValue), minValue(argMinValue), maxValue(argMaxValue), mouseDown(false) {
  size = Pos(200, 10);
  rect.setColor(Color(0.3f, 0.3f, 0.3f, 1.0f));
  rect.setSize(size);
  rect.setFill(true);
  updateValue((int)(getAbsPos().x + (curValue - minValue) / (maxValue - minValue) * size.x));
}

void Slider::onMouseButtonDown(const MouseEvent& me) {
  updateValue(me.x);
  if (!mouseDown) {
    mouseDown = true;
    root->lockMouse(this);
  }
}

void Slider::onMouseButtonUp(const MouseEvent& me) {
  if (mouseDown) {
    mouseDown = false;
    root->unlockMouse();
  }
}
void Slider::onMouseMove(const MouseEvent& me) {
  if (mouseDown) {
    updateValue(me.x);
  }
}

void Slider::updateValue(int mx) {
  Pos apos = getAbsPos();
  curValue = minValue + ((mx - apos.x) / size.x) * (maxValue - minValue);
  if (curValue < minValue)
    curValue = minValue;
  if (curValue > maxValue)
    curValue = maxValue;

  if (sliderCb[ToInt(SliderEventType::onChange)]) {
    sliderCb[ToInt(SliderEventType::onChange)](UIEvent(this, ToInt(SliderEventType::onChange)));
  }

  int x = (int)((curValue - minValue) * size.x / (maxValue - minValue));
  line.setSource(Pos((float)x, 0.0f));
  line.setDestination(Pos((float)x, size.y));
}

void Slider::draw() {
  RelOffsetGuard rog(pos);
  rect.draw();
  line.draw();
}

}  // namespace ui
}  // namespace glider
