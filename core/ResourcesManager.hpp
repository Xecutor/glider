#ifndef __GLIDER_RESOURCESMANAGER_HPP__
#define __GLIDER_RESOURCESMANAGER_HPP__

#include <map>
#include <string>

#include "Font.hpp"
#include "Managed.hpp"
#include "SdlFwdDecl.h"

namespace glider {

struct SurfaceHolder : public Managed {
  SDL_Surface* surf;
  using Ref = ReferenceTmpl<SurfaceHolder>;
  SurfaceHolder(SDL_Surface* argSurf = 0) : surf(argSurf) {
  }
  virtual ~SurfaceHolder();
};

class ResourcesManager {
public:
  ManagedObjectId addObject(Managed* obj) {
    return objList.insert(objList.end(), obj);
  }
  void removeObject(ManagedObjectId id) {
    objList.erase(id);
  }
  void reloadAll() {
    for (ManagedObjectsList::iterator it = objList.begin(), end = objList.end(); it != end; ++it) {
      (*it)->reload();
    }
  }

  Font::Ref getFont(const char* name, int size, int flags = ffHinting);
  SurfaceHolder::Ref getSurf(const char* name);

protected:
  ManagedObjectsList objList;

  struct FontSpec {
    std::string name;
    int size;
    int flags;
    FontSpec(const std::string& argName, int argSize, int argFlags) : name(argName), size(argSize), flags(argFlags) {
    }
    bool operator<(const FontSpec& other) const {
      return name < other.name || (name == other.name && size < other.size) ||
             (name == other.name && size == other.size && flags < other.flags);
    }
  };

  using FontsMap = std::map<FontSpec, Font::Ref>;
  FontsMap fonts;

  using SurfMap = std::map<std::string, SurfaceHolder::Ref>;
  SurfMap surfaces;
};

extern ResourcesManager manager;

}  // namespace glider

#endif
