#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>

inline void glErrorDebug() {
}

#ifdef DEBUG
#define GLCHK(x)                                                                      \
  x;                                                                                  \
  {                                                                                   \
    int err;                                                                          \
    if ((err = glGetError()) == 0) {                                                  \
    } else {                                                                          \
      glErrorDebug();                                                                 \
      fprintf(stderr, "failed with err=%d at line " __FILE__ ":%d\n", err, __LINE__); \
    }                                                                                 \
  }
#else
#define GLCHK(x) x
#endif
