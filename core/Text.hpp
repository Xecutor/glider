#pragma once

#include <string>
#include <vector>

#include "Drawable.hpp"
#include "Font.hpp"
#include "UString.hpp"
#include "Utility.hpp"
#include "VertexBuffer.hpp"

namespace glider {

class Text : public Drawable {
public:
  using Ref = ReferenceTmpl<Text>;

  Text(Font::Ref fnt = {}, std::string_view str = {}, bool rawText = false, int maxWidth = 0, bool wordWrap = true);
  Text(std::string_view str, bool rawText = false, int maxWidth = 0, bool wordWrap = true);
  virtual ~Text();
  void assignFont(Font::Ref argFnt) {
    fnt = argFnt;
    prepare(rawText);
  }
  void setText(std::string_view str, bool rawText = false, int maxWidth = 0, bool wordWrap = true);
  void setPosition(const Pos& argPos) {
    pos = argPos;
  }
  const Pos& getPosition() const {
    return pos;
  }
  void setColor(const Color& argClr) {
    clr = argClr;
    prepare(rawText);
  }
  void draw();
  void reload();

  int getWidth() const {
    return width;
  }

  int getHeight() const {
    return height;
  }

  void updateColors(const ClrVector& clrs, int from = 0, int to = -1);
  const ClrVector& getColors() const {
    return vb.getCBuf();
  }

  void getLetterExtent(size_t idx, Pos& argPos, Pos& argSize);
  size_t getTextLength() const {
    return str.getLength();
  }

  size_t getLinesCount() const {
    return linesCount;
  }

  const std::vector<size_t>& getLinesStart() const {
    return linesStart;
  }

  const UString& getUString() const {
    return str;
  }

  Font::Ref getFont() {
    return fnt;
  }

protected:
  Pos pos;
  Color clr;
  Font::Ref fnt;
  UString str;
  bool rawText;
  int maxWidth;
  bool wordWrap;
  int width;
  int height;
  size_t linesCount;
  std::vector<size_t> linesStart;
  VertexBuffer vb;
  void prepare(bool rawText);
};

}  // namespace glider
