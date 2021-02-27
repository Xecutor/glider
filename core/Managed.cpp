#include "Managed.hpp"

#include <unordered_map>

//#include "ResourcesManager.hpp"

namespace glider {

namespace {

struct WeakRecord {
  Managed* obj;
  uint32_t weakCount = 0;
  bool alive = true;
  WeakRecord(Managed* argObj) : obj(argObj) {
  }
};

std::unordered_map<uint32_t, WeakRecord>& getWeakStorage() {
  static std::unordered_map<uint32_t, WeakRecord> weakStorage;
  return weakStorage;
}

uint32_t makeNewWeakId() {
  static uint32_t lastWeakId = 0;
  auto& weakStorage = getWeakStorage();
  uint32_t rv;
  do {
    rv = ++lastWeakId;
  } while (rv == 0 || weakStorage.find(rv) != weakStorage.end());
  return rv;
}

}  // namespace

// Managed::Managed() : refCount(0) {
//   mngId=manager.addObject(this);
// }

Managed::~Managed() {
  // manager.removeObject(mngId);
  if (weakId) {
    auto& weakStorage = getWeakStorage();
    auto it = weakStorage.find(weakId);
    if (it != weakStorage.end()) {
      it->second.obj = nullptr;
      it->second.alive = false;
    }
  }
}

WeakReference::WeakReference(Managed* argObj) {
  if (argObj) {
    if (!argObj->weakId) {
      weakId = makeNewWeakId();
      argObj->weakId = weakId;
      auto& record = getWeakStorage().emplace(weakId, WeakRecord(argObj)).first->second;
      ++record.weakCount;
    } else {
      weakId = argObj->weakId;
      ref();
    }
  }
}

WeakReference::~WeakReference() {
  unref();
}

void WeakReference::ref() {
  if (weakId) {
    auto& record = getWeakStorage().find(weakId)->second;
    ++record.weakCount;
  }
}

void WeakReference::unref() {
  auto& weakStorage = getWeakStorage();
  auto it = weakStorage.find(weakId);
  if (it != weakStorage.end()) {
    auto& record = it->second;
    if (--record.weakCount == 0) {
      if (record.alive) {
        record.obj->weakId = 0;
      }
      weakStorage.erase(it);
    }
  }
}

Reference WeakReference::lockBase() const {
  if (!weakId) {
    return Reference();
  }
  auto& weakStorage = getWeakStorage();
  auto it = weakStorage.find(weakId);
  if (it == weakStorage.end() || !it->second.alive) {
    return Reference();
  }
  return Reference(it->second.obj);
}

WeakReference Reference::getWeakBase() const {
  return WeakReference(obj);
}

}  // namespace glider
