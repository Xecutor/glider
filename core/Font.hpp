#pragma once

#include "Managed.hpp"
#include "SdlFwdDecl.h"
#include "Texture.hpp"
#include "UString.hpp"
#include "Utility.hpp"

namespace glider {

struct GlyphInfo {
  GlyphInfo() : init(false) {
  }
  Pos texPos;
  Pos texSize;
  float minx, miny, maxx, maxy;
  float adv;
  int xshift, yshift;
  bool init;
};

enum FontFlags { ffHinting = 1, ffBold = 2, ffGlow = 4 };

class Font : public Managed {
public:
  using Ref = ReferenceTmpl<Font>;

  Font();
  virtual ~Font();
  void reload();
  void loadTTF(const char* argFileName, int size, int argFlags);
  const std::string& getFileName() const {
    return fileName;
  }
  int getSize() const {
    return size;
  }
  int getFlags() const {
    return flags;
  }
  const Texture& getTexture() const {
    return tex;
  }
  GlyphInfo getGlyph(ushort glyph);
  void prepareForString(const UString& str);

  void setTexSize(int argTexSize) {
    texSize = argTexSize;
  }
  int getTexSize() const {
    return texSize;
  }

  int getHeight() const;
  int getLineSkip() const;
  int getAscent() const;
  int getLineWidth(const char* line) {
    int w = 0;
    UString us(line, strlen(line));
    ushort c;
    size_t pos = 0;
    while ((c = us.getNext(pos))) {
      w += (int)getGlyph(c).adv;
    }
    return w;
  }

protected:
  std::string fileName;
  int size;
  int flags;
  TTF_Font* font;
  SDL_Surface* img;
  Texture tex;
  int curX;
  int curY;
  int nextY;

  int texSize;

  GlyphInfo* glyphs[256];

  bool prepareGlyph(ushort c);
  void updateTex();

  GlyphInfo& getGIRef(ushort c);
};

}  // namespace glider
