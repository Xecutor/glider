#include "Label.hpp"

#include "GLState.hpp"
#include "UIConfig.hpp"

namespace glider {
namespace ui {

Label::Label(std::string_view argCaption, std::string_view argName) {
  drawShadow = false;
  caption.assignFont(uiConfig.getLabelFont());
  caption.setColor(uiConfig.getColor("labelTextColor"));
  captionShadow.assignFont(uiConfig.getLabelFont());
  captionShadow.setPosition(Pos(1, 1));
  captionShadow.setColor(uiConfig.getColor("labelShadowColor"));
  if (!argCaption.empty()) {
    setCaption(argCaption);
  }
  if (!argName.empty()) {
    setName(argName);
  }
}

void Label::draw() {
  RelOffsetGuard rog(pos);
  if (drawShadow) {
    captionShadow.draw();
  }
  caption.draw();
}

}  // namespace ui
}  // namespace glider
