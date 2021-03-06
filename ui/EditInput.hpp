#pragma once

#include <string>

#include "Line.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"
#include "UIAnimation.hpp"
#include "UIObject.hpp"

namespace glider::ui {

enum EditInputEventType { eiOnAccept, eiOnCancel, eiOnModify, eiCount };

class EditInput : public UIObject {
public:
  EditInput(const char* name = 0);
  void draw();
  void setValue(const std::string& argValue);
  const std::string& getValue() const {
    return value;
  }
  int getIntValue() const {
    return std::stoi(value);
  }
  size_t getCurPos() const {
    return curPos;
  }
  void setCurPos(size_t argCurPos, bool extendSelection = false);
  void insertText(const char* txt);
  void resetSelection();

  using UIObject::setEventHandler;
  EditInput& setEventHandler(EditInputEventType et, UICallBack cb) {
    eiCb[et] = cb;
    return *this;
  }

protected:
  std::string value;
  Text text;
  Line cursor;
  Rectangle rect;
  Rectangle selection;
  int hShift;
  bool selecting;

  UICallBack eiCb[eiCount];

  void deleteSymbol(int dir);

  class CursorBlinkAnimation : public UIAnimation {
  public:
    CursorBlinkAnimation() : active(false) {
    }
    EditInput* ei = nullptr;
    bool active;
    void onStart() {
      active = true;
    }
    void onEnd() {
      active = false;
    }
    bool update(int mcsec) {
      return active && ei->cursorBlinkAnimation(mcsec);
    }
    bool deleteOnFinish() {
      return false;
    }
  };
  CursorBlinkAnimation curBlinkAni;
  int lastCurBlink;
  size_t curPos;
  size_t selStart, selEnd;
  bool haveSelection() const {
    return selStart != selEnd;
  }
  bool isCurVisible;
  bool cursorBlinkAnimation(int mcsec);
  int mouseXToCurPos(int x);
  struct ScrollAnimation : public UIAnimation {
  public:
    ScrollAnimation() : ei(0), isCancelled(false) {
    }
    EditInput* ei;
    bool isCancelled;
    bool update(int mcsec) {
      if (!isCancelled) {
        ei->scroll(mcsec);
      }
      return !isCancelled;
    }
    bool deleteOnFinish() {
      return false;
    }
    void cancel() {
      isCancelled = true;
    }
  };
  ScrollAnimation scrollAni;
  int scrollTimer;
  int scrollDir;
  void scroll(int mcsec);

  void onFocusGain();
  void onFocusLost();
  void onKeyDown(const KeyboardEvent& ke);
  void onKeyPress(const KeyboardEvent& ke);
  void onMouseButtonDown(const MouseEvent& me);
  void onMouseButtonUp(const MouseEvent& me);
  void onMouseMove(const MouseEvent& me);

  void onObjectResize();
};

}  // namespace glider::ui
