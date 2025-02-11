#include <functional>
#include <type_traits>
#include <vector>

namespace kst {

template <class T>
class ObservableProperty {
public:
  using ArgType = std::conditional_t<std::is_trivial_v<T>, T, const T&>;
  using OnChangeFunc = std::function<void(ArgType)>;

  ObservableProperty() = default;

  ObservableProperty(ArgType initValue) : value(initValue) {
  }

  void setValue(ArgType newValue) {
    value = newValue;
    notify();
  }

  ArgType getValue() const {
    return value;
  }

  ObservableProperty<T>& operator=(ArgType newValue) {
    setValue(newValue);
    return *this;
  }

  template <class S>
  uint32_t subscribe(S&& s) {
    uint32_t rv = lastId++;
    subs.emplace_back(rv, std::forward<S>(s));
    return rv;
  }

  void unsubscribe(uint32_t id) {
    subs.erase(std::remove_if(subs.begin(), subs.end(), [id](const auto& p) { return p.first == id; }), subs.end());
  }

private:
  void notify() {
    for (auto& p : subs) {
      if (p.second) {
        p.second(value);
      }
    }
  }

  T value;
  uint32_t lastId = 0;
  std::vector<std::pair<uint32_t, OnChangeFunc>> subs;
};

}  // namespace kst
