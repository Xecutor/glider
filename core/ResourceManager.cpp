#include "ResourcesManager.hpp"
#include "SysHeaders.hpp"
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

namespace glider {

ResourcesManager manager;

SurfaceHolder::~SurfaceHolder() {
  if (surf) {
    SDL_FreeSurface(surf);
  }
}

Font::Ref ResourcesManager::getFont(const char* name, int size, int flags) {
  FontsMap::iterator it = fonts.find(FontSpec(name, size, flags));
  if (it != fonts.end()) {
    return it->second;
  }
  auto rv = MakeRef<Font>();
  fonts.emplace(FontSpec(name, size, flags), rv);
  rv->loadTTF(name, size, flags);
  return rv;
}

SurfaceHolder::Ref ResourcesManager::getSurf(const char* name) {
  SurfMap::iterator it = surfaces.find(name);
  if (it != surfaces.end()) {
    return it->second;
  }
  SDL_Surface* surf = IMG_Load(name);
  auto rv = MakeRef<SurfaceHolder>(surf);
  surfaces.emplace(name, rv);
  return rv;
}

}  // namespace glider
