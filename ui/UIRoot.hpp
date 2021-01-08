#pragma once

#include "UIAnimation.hpp"
#include "UIContainer.hpp"

namespace glider::ui {

using UserCallback = EventCallback<>;

class UIRoot : public UIContainer, public EventHandler {
public:
  UIRoot();
  void onActiveChange(bool active);
  void onMouseEvent(MouseEvent& argEvent);
  void onKeyboardEvent(KeyboardEvent& argEvent);
  static void postMouseEvent(const MouseEvent& argEvent, UIObject& obj);
  static void postKeyboardEvent(const KeyboardEvent& argEvent, UIObject& obj);
  void onResize();
  void onQuit();
  void onFrameUpdate(int mcsec);
  void onUserEvent(void* data1, void* data2);
  void lockMouse(UIObject::Ref obj) {
    mouseLock.push_back(obj);
  }
  void unlockMouse() {
    if (mouseLock.empty()) {
      KSTHROW("unbalanced mouse unlock!");
    }
    mouseLock.pop_back();
  }
  bool isMouseLocked() const {
    return !mouseLock.empty();
  }
  void setKeyboardFocus(UIObject::Ref obj) {
    if (keyFocus.isAssigned() && keyFocus != obj) {
      keyFocus->removeFocus();
    }
    keyFocus = obj;
  }
  static void init();
  static void shutdown();
  void addAnimation(UIAnimation* argAni);
  void removeAnimation(UIAnimation* argAni);

  void replaceLoop(UIObject::Ref obj);
  void modalLoop(UIObject::Ref obj);

  void exitModal();

protected:
  UIObject::Ref keyFocus;
  UIObjectsList mouseLock;
  typedef std::list<UIAnimation*> AniList;
  AniList animations;
  Pos mouseButtonPressPos;
};

extern UIRoot* root;

}  // namespace glider::ui
