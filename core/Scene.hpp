#pragma once

#include <list>

#include "Drawable.hpp"

namespace glider {

typedef std::list<Drawable::Ref> DrawableObjectsList;
typedef DrawableObjectsList::iterator DrawableObjectId;

class Scene : public Drawable {
public:
  void draw();
  DrawableObjectId addObject(Drawable* argObject);
  void removeObject(DrawableObjectId id);
  void clear();
  DrawableObjectId begin() {
    return objects.begin();
  }
  DrawableObjectId end() {
    return objects.end();
  }

protected:
  DrawableObjectsList objects;
};

}  // namespace glider
