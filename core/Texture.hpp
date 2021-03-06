#pragma once

#include "Drawable.hpp"
#include "SdlFwdDecl.h"
#include "Utility.hpp"

namespace glider {

class Texture {
public:
  Texture();
  virtual ~Texture();
  void bind() const;
  void unbind() const;
  void create(int argWidth, int argHeight);
  void loadSurface(SDL_Surface* img);
  int getTexWidth() const {
    return texWidth;
  }
  int getTexHeight() const {
    return texHeight;
  }
  void renderHere(Drawable* obj);
  void recreate();
  void setLinearMagFiltering();
  void setLinearMinFiltering();
  void setNearestMagFiltering();
  void setNearestMinFiltering();
  void setClump();
  void setRepeat();
  void setMirroredRepeat();
  void clear();

protected:
  uint texId;
  uint fboId;
  int texWidth, texHeight;
};

}  // namespace glider
