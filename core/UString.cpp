#include "UString.hpp"

#include <memory.h>

namespace glider {

UString::UString(const char* argStr, size_t argLength) : UString() {
  bytes = argLength;
  if (bytes > 0) {
    capacity = argLength + 1;
    str = new char[capacity];
    fprintf(stderr, "new1 %p[%zu]\n", str, capacity);
    memcpy(str, argStr, bytes);
    str[bytes] = 0;
    updateLength();
  }
}

UString::UString(const UString& argStr) {
  argStr.updateLength();
  bytes = argStr.bytes;
  capacity = argStr.capacity;
  str = new char[capacity];
  fprintf(stderr, "new2 %p[%zu]\n", str, capacity);
  memcpy(str, argStr.str, capacity);
  symbols = argStr.symbols;
  modified = false;
}

UString::UString(UString&& argStr) noexcept {
  bytes = argStr.bytes;
  capacity = argStr.capacity;
  str = argStr.str;
  symbols = argStr.symbols;
  modified = argStr.modified;
  fprintf(stderr, "move %p[%zu]\n", str, capacity);
  argStr.str = nullptr;
  argStr.symbols = 0;
  argStr.capacity = 0;
  argStr.bytes = 0;
  argStr.modified = false;
}

UString::~UString() {
  deleteStr();
}

UString& UString::operator=(std::string_view argStr) {
  bytes = argStr.length();
  if (argStr.empty()) {
    bytes = 0;
    symbols = 0;
    modified = false;
    return *this;
  }
  if (bytes >= capacity) {
    capacity = bytes + 1;
    deleteStr();
    str = new char[capacity];
    fprintf(stderr, "new3 %p[%zu]\n", str, capacity);
  }
  memcpy(str, argStr.data(), argStr.length());
  str[bytes] = 0;
  modified = true;
  return *this;
}

UString& UString::operator=(const UString& argStr) {
  if (argStr.bytes == 0) {
    bytes = 0;
    symbols = 0;
    modified = false;
    return *this;
  }
  bytes = argStr.bytes;
  if (bytes >= capacity) {
    capacity = bytes + 1;
    deleteStr();
    str = new char[capacity];
    fprintf(stderr, "new4 %p[%zu]\n", str, capacity);
  }
  memcpy(str, argStr.str, argStr.bytes + 1);
  modified = true;
  return *this;
}

UString& UString::operator=(UString&& argStr) {
  deleteStr();
  bytes = argStr.bytes;
  capacity = argStr.capacity;
  str = argStr.str;
  symbols = argStr.symbols;
  modified = false;
  fprintf(stderr, "move2 %p[%zu]\n", str, capacity);
  argStr.str = nullptr;
  argStr.symbols = 0;
  argStr.capacity = 0;
  argStr.bytes = 0;
  argStr.modified = false;
  return *this;
}

UString& UString::operator+=(const UString& rhs) {
  if (bytes + rhs.bytes >= capacity) {
    capacity = bytes + rhs.bytes;
    capacity += capacity / 2 + 1;
    char* newstr = new char[capacity];
    fprintf(stderr, "new+= %p[%zu]\n", newstr, capacity);
    memcpy(newstr, str, bytes);
    deleteStr();
    str = newstr;
  }
  memcpy(str + bytes, rhs.str, rhs.bytes);
  bytes += rhs.bytes;
  str[bytes] = 0;
  modified = true;
  return *this;
}

size_t UString::getNextPos(const char* argStr, size_t pos) {
  uint c = (unsigned char)argStr[pos];
  pos++;
  if (c < 0x80) {
    return pos;
  } else if ((c >> 5) == 0x06) {
    return pos + 1;
  } else if ((c >> 4) == 0x0e) {
    return pos + 2;
  } else if ((c >> 3) == 0x1e) {
    return pos + 3;
  }
  return pos;
}

ushort UString::getNext(size_t& pos) const {
  if (pos >= bytes) {
    return 0;
  }
  uint c = getNextSymbol(str, pos);
  return (ushort)c;
}

size_t UString::calcLength(const char* str, size_t bytes) {
  size_t symbols = 0;
  for (size_t i = 0; i < bytes; symbols++) {
    unsigned char c = str[i];
    if (c < 0x80) {
      i++;
    } else if ((c >> 5) == 0x06) {
      i += 2;
    } else if ((c >> 4) == 0x0e) {
      i += 3;
    } else if ((c >> 3) == 0x1e) {
      i += 4;
    } else {
      // error?
      i++;
    }
  }
  return symbols;
}

void UString::updateLength() const {
  symbols = calcLength(str, bytes);
  modified = false;
}

size_t UString::getLetterOffset(size_t idx) const {
  size_t rv = 0;
  for (size_t i = 0; i < idx; i++) {
    getNext(rv);
  }
  return rv;
}

ushort UString::getNextSymbol(const char* str, size_t& pos) {
  uint c = (unsigned char)str[pos];
  pos++;
  if (c < 0x80) {
    return (ushort)c;
  } else if ((c >> 5) == 0x06) {
    c = ((c << 6) & 0x7ff) + (str[pos++] & 0x3f);
  } else if ((c >> 4) == 0x0e) {
    c = ((c << 12) & 0xffff) | ((((uint)(uchar)str[pos++]) << 6) & 0x0fff);
    c |= (str[pos++] & 0x3f);
  } else if ((c >> 3) == 0x1e) {
    c = ((c << 18) & 0x1fffff) + ((((uint)(uchar)str[pos++]) << 12) & 0x0003ffff);
    c |= (((uint)(uchar)str[pos++]) << 6) & 0x0fff;
    c |= ((uint)(uchar)str[pos++]) & 0x3f;
  } else {
    c = ' ';
  }
  return (ushort)c;
}

size_t UString::ucs2ToUtf8(ushort symbol, char* buf) {
  size_t rv = 0;
  if (symbol < 0x80) {
    buf[rv++] = symbol & 0xff;
  } else if (symbol < 0x800) {
    buf[rv++] = ((symbol >> 6) | 0xc0) & 0xff;
    buf[rv++] = (symbol & 0x3f) | 0x80;
  } else {
    buf[rv++] = ((symbol >> 12) | 0xe0) & 0xff;
    buf[rv++] = ((symbol >> 6) & 0x3f) | 0x80;
    buf[rv++] = (symbol & 0x3f) | 0x80;
  }
  buf[rv] = 0;
  return rv;
}

}  // namespace glider
