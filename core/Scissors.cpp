#include "Scissors.hpp"

#include "GLState.hpp"
#include "SysHeaders.hpp"

namespace glider {

void Scissors::draw() {
  state.enableScissors(rect);
  obj->draw();
  state.disableScissors();
}

void Scissors::draw(Drawable* argObj) {
  state.enableScissors(rect);
  argObj->draw();
  state.disableScissors();
}

}  // namespace glider
