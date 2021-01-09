#pragma once

#include "Drawable.hpp"
#include "ResourcesManager.hpp"
#include "SdlFwdDecl.h"
#include "Texture.hpp"
#include "Utility.hpp"

namespace glider {

class Image : public Drawable, public Texture {
public:
  using Ref = ReferenceTmpl<Image>;

  Image();
  virtual ~Image();
  void draw();
  void reload();
  void update();
  void load(const char* argFileName);
  void create(int argWidth, int argHeight, bool allocate = false);
  void setPosition(const Pos& argPos) {
    pos = argPos;
  }
  const Pos& getPosition() const {
    return pos;
  }
  void setCenter(const Pos& argCenter) {
    centerPos = argCenter;
  }
  void setAngle(float argAngle) {
    angle = argAngle;
  }
  void setScale(float argScale) {
    scaleX = argScale;
    scaleY = argScale;
  }
  void setColor(const Color& argColor) {
    color = argColor;
  }
  void setScaleXY(float argScaleX, float argScaleY) {
    scaleX = argScaleX;
    scaleY = argScaleY;
  }
  void setTexRect(const Rect& argTexRect) {
    texRect = argTexRect;
  }
  const Pos& getSize() const {
    return size;
  }
  Pos getScaledSize() const {
    return Pos(size.x * scaleX, size.y * scaleY);
  }
  Color getPixel(int x, int y);
  void setPixel(int x, int y, Color clr);

protected:
  SurfaceHolder::Ref surf;
  Pos pos;
  Pos centerPos;
  Pos size;
  Rect texRect;
  Color color;
  float angle;
  float scaleX, scaleY;
};

}  // namespace glider
