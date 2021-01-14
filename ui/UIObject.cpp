#include "UIObject.hpp"

#include <stdio.h>

#include "UIRoot.hpp"

namespace glider {
namespace ui {

static int UIObjectUidSeq = 0;

UIObject::UIObject(std::string_view argName) : parent(0), intTag(0) {
  uid = UIObjectUidSeq++;
  if (argName.empty()) {
    char buf[32];
    sprintf(buf, "object%d", uid);
    name = buf;
  } else {
    name = argName;
  }
  focused = false;
  tabStop = false;
  visible = true;
  tabOrder = 0;
  log = kst::Logger::getLogger("obj");
}

void UIObject::onMouseEnter(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseEnter;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseLeave(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseLeave;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseButtonDown(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseButtonDown;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseButtonUp(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseButtonUp;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseClick(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseClick;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseMove(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseMove;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onMouseScroll(const MouseEvent& me) {
  const UIEventType et = UIEventType::mouseScroll;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, me);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onKeyDown(const KeyboardEvent& ke) {
  const UIEventType et = UIEventType::keyDown;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, ke);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onKeyUp(const KeyboardEvent& ke) {
  const UIEventType et = UIEventType::keyUp;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, ke);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::onKeyPress(const KeyboardEvent& ke) {
  const UIEventType et = UIEventType::keyPress;
  if (cbArray[ToInt(et)]) {
    UIEvent evt(et, ke);
    cbArray[ToInt(et)](evt);
  }
}

void UIObject::setFocus() {
  if (!focused) {
    focused = true;
    if (isTabStop())
      root->setKeyboardFocus(this);
    onFocusGain();
  }
}

void UIObject::removeFocus() {
  if (focused) {
    focused = false;
    root->setKeyboardFocus(nullptr);
    onFocusLost();
    if (parent)
      parent->removeFocus();
  }
}

}  // namespace ui
}  // namespace glider
