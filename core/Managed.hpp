#pragma once

#include <stdint.h>

#include <list>

namespace glider {

class Managed;

using ManagedObjectsList = std::list<Managed*>;
using ManagedObjectId = ManagedObjectsList::iterator;

class Reference;
class WeakReference;

class Managed {
public:
  Managed() = default;

  virtual ~Managed();

  virtual void reload() {
  }

protected:
  // ManagedObjectId mngId;
  uint32_t refCount = 0;
  uint32_t weakId = 0;
  friend class Reference;
  friend class WeakReference;
};

class WeakReference {
public:
  WeakReference() = default;

  explicit WeakReference(Managed* argObj);

  WeakReference(const WeakReference& argRef) : weakId(argRef.weakId) {
    ref();
  }

  WeakReference(WeakReference&& argRef) noexcept : weakId(argRef.weakId) {
    argRef.weakId = 0;
  }

  ~WeakReference();

  WeakReference& operator=(const WeakReference& argRef) {
    if (this == &argRef) {
      return *this;
    }
    unref();
    weakId = argRef.weakId;
    ref();
    return *this;
  }

  WeakReference& operator=(WeakReference&& argRef) {
    if (this == &argRef) {
      return *this;
    }
    weakId = argRef.weakId;
    argRef.weakId = 0;
    return *this;
  }

  bool operator==(const WeakReference& argRef) const noexcept {
    return weakId == argRef.weakId;
  }

  bool operator!=(const WeakReference& argRef) const noexcept {
    return weakId != argRef.weakId;
  }

protected:
  uint32_t weakId = 0;

protected:
  void ref();

  void unref();

  Reference lockBase() const;
};

class Reference {
public:
  Reference(Managed* argObj = nullptr) noexcept : obj(argObj) {
    ref();
  }

  Reference(const Reference& argRef) noexcept : obj(argRef.obj) {
    ref();
  }

  Reference(Reference&& argRef) noexcept : obj(argRef.obj) {
    argRef.obj = nullptr;
  }

  ~Reference() {
    unref();
  }

  Reference& operator=(Managed* argObj) noexcept {
    if (obj != argObj) {
      unref();
      obj = argObj;
      ref();
    }
    return *this;
  }

  Reference& operator=(const Reference& argRef) noexcept {
    if (this == &argRef) {
      return *this;
    }
    unref();
    obj = argRef.obj;
    ref();
    return *this;
  }

  Reference& operator=(Reference&& argRef) noexcept {
    unref();
    obj = argRef.obj;
    argRef.obj = nullptr;
    return *this;
  }

  bool isAssigned() const noexcept {
    return obj != nullptr;
  }

protected:
  mutable Managed* obj;

protected:
  void ref() const {
    if (obj) {
      ++obj->refCount;
    }
  }

  void unref() const {
    if (obj) {
      if (--obj->refCount == 0) {
        delete obj;
        obj = nullptr;
      }
    }
  }

  WeakReference getWeakBase() const;
};

template <class T>
class WeakReferenceTmpl;

template <class T>
class ReferenceTmpl : public Reference {
public:
  ReferenceTmpl(T* argObj = nullptr) : Reference(argObj) {
  }

  ReferenceTmpl(const ReferenceTmpl& argRef) : Reference(argRef) {
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  ReferenceTmpl(ReferenceTmpl<U> argRef) : Reference(argRef) {
  }

  ReferenceTmpl& operator=(T* argObj) {
    Reference::operator=(argObj);
    return *this;
  }

  ReferenceTmpl& operator=(const ReferenceTmpl& argRef) {
    Reference::operator=(argRef);
    return *this;
  }

  ReferenceTmpl& operator=(ReferenceTmpl&& argRef) {
    Reference::operator=(std::move(argRef));
    return *this;
  }

  bool operator==(const ReferenceTmpl& rhs) const {
    return obj == rhs.obj;
  }

  bool operator!=(const ReferenceTmpl& rhs) const {
    return obj != rhs.obj;
  }

  T* get() {
    return static_cast<T*>(obj);
  }

  const T* get() const {
    return static_cast<const T*>(obj);
  }

  T* operator->() {
    return static_cast<T*>(obj);
  }

  const T* operator->() const {
    return static_cast<const T*>(obj);
  }

  T& operator*() {
    return *static_cast<T*>(obj);
  }

  const T& operator*() const {
    return *static_cast<const T*>(obj);
  }

  template <class U>
  ReferenceTmpl<U> as() {
    return dynamic_cast<U*>(obj);
  }

  template <class U>
  ReferenceTmpl<const U> as() const {
    return dynamic_cast<const U*>(obj);
  }

  WeakReferenceTmpl<T> getWeak();

protected:
  ReferenceTmpl(Reference&& argRef) : Reference(std::move(argRef)) {
  }

  friend class WeakReferenceTmpl<T>;
};

template <class T>
class WeakReferenceTmpl : WeakReference {
public:
  WeakReferenceTmpl() = default;

  WeakReferenceTmpl(T* argObj) : WeakReference(argObj) {
  }

  WeakReferenceTmpl(const WeakReferenceTmpl&) = default;

  WeakReferenceTmpl(WeakReferenceTmpl&&) = default;

  WeakReferenceTmpl& operator=(const WeakReferenceTmpl&) = default;

  WeakReferenceTmpl& operator=(WeakReferenceTmpl&&) = default;

  ReferenceTmpl<T> lock() const {
    return lockBase();
  }

protected:
  WeakReferenceTmpl(WeakReference&& argRef) : WeakReference(std::move(argRef)) {
  }
  friend class ReferenceTmpl<T>;
};

template <class T>
WeakReferenceTmpl<T> ReferenceTmpl<T>::getWeak() {
  return getWeakBase();
}

template <class T, class... Args>
ReferenceTmpl<T> MakeRef(Args&&... args) {
  return new T(std::forward<Args>(args)...);
}

}  // namespace glider
