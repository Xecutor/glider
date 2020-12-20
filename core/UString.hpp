#ifndef __GLIDER_USTRING_HPP__
#define __GLIDER_USTRING_HPP__

#include "Utility.hpp"

namespace glider{

class UString{
public:
  UString():str(0),bytes(0),capacity(0),symbols(0),modified(false){}
  UString(const char* argStr,size_t argLength);
  UString(const UString& argStr);
  ~UString();
  UString& operator+=(const UString& rhs);
  UString& operator=(const char* argStr);
  ushort getNext(size_t& pos)const;
  static size_t getNextPos(const char* argStr,size_t pos);
  static ushort getNextSymbol(const char* argStr,size_t& pos);
  static size_t calcLength(const char* str,size_t bytes);
  size_t getSize()const
  {
    return bytes;
  }
  size_t getLength()const
  {
    if(modified)
    {
      updateLength();
    }
    return symbols;
  }

  bool isEmpty()const
  {
    return bytes==0;
  }

  size_t getLetterOffset(size_t idx)const;

  static size_t ucs2ToUtf8(ushort symbol,char* buf);

protected:
  char* str;
  size_t bytes;
  size_t capacity;
  mutable size_t symbols;
  mutable size_t modified;

  void updateLength()const;
};

}

#endif
