#pragma once

#include "Font.hpp"
#include "Text.hpp"
#include "UIObject.hpp"

namespace glider::ui {

class Label : public UIObject {
public:
  using Ref = ReferenceTmpl<Label>;
  Label(std::string_view argCaption = {}, std::string_view argName = {});

  void assignFont(FontRef argFont) {
    caption.assignFont(argFont);
  }
  void setColor(Color clr) {
    caption.setColor(clr);
  }
  void setShadowColor(Color clr) {
    captionShadow.setColor(clr);
  }
  void setCaption(std::string_view argCaption, int argMaxWidth = 0, bool argRawText = false, bool agrWordWrap = true) {
    captionText = argCaption;
    caption.setText(argCaption, argRawText, argMaxWidth, agrWordWrap);
    if (drawShadow) {
      captionShadow.setText(argCaption);
    }
    size = Pos((float)caption.getWidth(), (float)caption.getHeight());
  }
  const std::string& getCaption() const {
    return captionText;
  }
  void setShadowOffset(Pos off) {
    captionShadow.setPosition(off);
  }
  void enableShadow() {
    drawShadow = true;
    captionShadow.setText(captionText.c_str());
  }
  void disableShadow() {
    drawShadow = false;
  }
  void draw();

protected:
  std::string captionText;
  Text caption;
  Text captionShadow;
  bool drawShadow;
};

}  // namespace glider::ui
