cmake_minimum_required(VERSION 3.10)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW)

find_library(SDL2_IMAGE_LIB SDL2_image)
find_library(SDL2_TTF_LIB SDL2_ttf)
message("SDL2_IMAGE_LIB=${SDL2_IMAGE_LIB}")

include_directories(core ui)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

file (GLOB CORE_FILES core/*.cpp )
file (GLOB UI_FILES ui/*.cpp )


cmake_policy(SET CMP0003 NEW)
add_library(glider-core STATIC ${CORE_FILES})

target_link_libraries(glider-core
  SDL2::SDL2
  SDL2::SDL2main
  GLEW::GLEW
  ${SDL2_IMAGE_LIB}
  ${SDL2_TTF_LIB}
  kst
  OpenGL::GL)

add_library(glider-ui STATIC ${UI_FILES})
target_link_libraries(glider-ui glider-core)

add_subdirectory(tests)
add_subdirectory(kst)

target_include_directories(glider-core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
)

target_include_directories(glider-ui PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ui>
)