#pragma once

#include <functional>

namespace glider::ui {

template <class... ARGS>
using EventCallback = std::function<void(ARGS...)>;

#define MKCALLBACK(methodName)                                                                                 \
  [wptr = glider::WeakReferenceTmpl<std::remove_reference_t<decltype(*this)>>{this}](auto&&... args) mutable { \
    auto ptr = wptr.lock();                                                                                    \
    if (ptr.isAssigned()) {                                                                                    \
      ptr->methodName(std::forward<decltype(args)>(args)...);                                                  \
    }                                                                                                          \
  }

}  // namespace glider::ui
