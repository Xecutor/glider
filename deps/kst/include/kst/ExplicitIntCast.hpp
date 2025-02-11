#pragma once

namespace kst {

template <class T>
struct ExplicitIntCastHelper {
  ExplicitIntCastHelper(T argValue) : value(argValue) {
  }

  template <class U>
  operator U() const {
    return static_cast<U>(value);
  }

  T value;
};

template <class T>
ExplicitIntCastHelper<T> ExplicitIntCast(T value) {
  return value;
}

}  // namespace kst
