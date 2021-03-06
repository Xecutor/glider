#include "Line.hpp"

#include "GLState.hpp"
#include "SysHeaders.hpp"

namespace glider {

void Line::draw() {
  state.loadIdentity();
  state.disableTexture();
  state.translate(Pos(0.5f, 0.5f));
  glLineWidth(width);
  glBegin(GL_LINES);
  srcColor.select();
  src.select();
  dstColor.select();
  dst.select();
  glEnd();
}

}  // namespace glider
