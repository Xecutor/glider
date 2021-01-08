#pragma once

#include "Utility.hpp"

namespace glider {

class UString {
public:
  UString() = default;
  UString(const char* argStr, size_t argLength);
  UString(std::string_view argStr) : UString(argStr.data(), argStr.length()) {
  }
  UString(const UString& argStr);
  UString(UString&& argStr) noexcept;
  ~UString();
  UString& operator+=(const UString& rhs);
  UString& operator=(std::string_view argStr);
  UString& operator=(const UString& argStr);
  UString& operator=(UString&& argStr);
  ushort getNext(size_t& pos) const;
  static size_t getNextPos(const char* argStr, size_t pos);
  static ushort getNextSymbol(const char* argStr, size_t& pos);
  static size_t calcLength(const char* str, size_t bytes);
  size_t getSize() const {
    return bytes;
  }
  size_t getLength() const {
    if (modified) {
      updateLength();
    }
    return symbols;
  }

  bool isEmpty() const {
    return bytes == 0;
  }

  size_t getLetterOffset(size_t idx) const;

  static size_t ucs2ToUtf8(ushort symbol, char* buf);

protected:
  char* str = nullptr;
  size_t bytes = 0;
  size_t capacity = 0;
  mutable size_t symbols = 0;
  mutable size_t modified = false;

  void updateLength() const;

  void deleteStr() {
    if (str) {
      fprintf(stderr, "del %p\n", str);
      delete[] str;
      str = nullptr;
    }
  }
};

}  // namespace glider
