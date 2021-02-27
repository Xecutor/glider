#pragma once

#include "Image.hpp"
#include "UIObject.hpp"

namespace glider::ui {

class Picture : public UIObject {
public:
  using Ref = ReferenceTmpl<Picture>;
  void draw();
  void assignImage(Image::Ref argImage) {
    image = argImage;
  }
  Image& getImage() {
    return *image;
  }
  const Image& getImage() const {
    return *image;
  }

protected:
  Image::Ref image;
};

}  // namespace glider::ui
