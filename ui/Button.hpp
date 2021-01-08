#pragma once

#include "Control.hpp"
#include "Rectangle.hpp"
#include "Scissors.hpp"
#include "Text.hpp"
#include "UIAnimation.hpp"

namespace glider::ui {

enum ButtonEventType { betOnClick, betCount };

class Button : public Control {
public:
  using Ref = ReferenceTmpl<Button>;

  Button(std::string_view argCaption = {}, std::string_view argName = {}, UICallBack cb = UICallBack());
  ~Button();
  void setCaption(std::string_view argCaption);
  void draw();

  using UIObject::setEventHandler;
  Button& setEventHandler(ButtonEventType et, UICallBack cb) {
    btnCb[et] = cb;
    return *this;
  }

protected:
  Rectangle tmpRect;
  Text caption;
  Text captionShade;
  Scissors capSciss;
  bool buttonDown;
  bool mouseOver;

  friend struct BtnAnimation;
  struct BtnAnimation : public UIAnimation {
    Button* btn;
    bool update(int mcs) {
      return btn->updateAnimation(mcs);
    }
    bool deleteOnFinish() {
      return false;
    }
  };
  BtnAnimation ani;

  Color oldClr, newClr;
  void changeClr(Color argNewClr);
  Color getCurrentClr();

  int aniMaxCnt;
  int aniCnt;
  void startAnimation();
  bool updateAnimation(int mcs);

  UICallBack btnCb[betCount];

  void setHoverState();
  void setDownState();
  void setNormalState();

  void onMouseMove(const MouseEvent& me);
  void onMouseEnter(const MouseEvent& me);
  void onMouseLeave(const MouseEvent& me);
  void onMouseButtonDown(const MouseEvent& me);
  void onMouseButtonUp(const MouseEvent& me);
  void onMouseClick(const MouseEvent& me);
};

}  // namespace glider::ui
