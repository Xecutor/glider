#pragma once

#include <kst/Throw.hpp>
#include <map>

#include "Font.hpp"

namespace glider::ui {

class UIConfig {
public:
  void init();
  void shutdown();
  Font::Ref getButtonFont() {
    return buttonFont;
  }
  Font::Ref getLabelFont() {
    return labelFont;
  }

  Font::Ref getWindowTitleFont() {
    return windowTitleFont;
  }

  Font::Ref getEditLineFont() {
    return editLineFont;
  }

  Color getClearColor() {
    return clearColor;
  }

  void setClearColor(Color clr);

  Color getEditLineFontColor() {
    return editLineFontColor;
  }

  float getConst(const std::string& name) {
    ConstsMap::iterator it = constsMap.find(name);
    if (it == constsMap.end()) {
      KSTHROW("Unknown constant %{}", name);
    }
    return it->second;
  }

  void setConst(const std::string& name, float value) {
    constsMap.insert(ConstsMap::value_type(name, value));
  }

  Color getColor(const std::string& name) {
    ColorsMap::iterator it = colorsMap.find(name);
    if (it == colorsMap.end()) {
      KSTHROW("Unknown color %{}", name);
    }
    return it->second;
  }

  void setColor(const std::string& name, Color value) {
    colorsMap.insert(ColorsMap::value_type(name, value));
  }

protected:
  Font::Ref buttonFont;
  Font::Ref labelFont;
  Font::Ref windowTitleFont;
  Font::Ref editLineFont;

  typedef std::map<std::string, float> ConstsMap;
  ConstsMap constsMap;

  typedef std::map<std::string, Color> ColorsMap;
  ColorsMap colorsMap;

  Color clearColor;
  Color editLineFontColor;
};

extern UIConfig uiConfig;

}  // namespace glider::ui
