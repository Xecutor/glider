cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0003 NEW)

project(glider)

if(NOT VCPKG_ROOT AND DEFINED ENV{VCPKG_ROOT})
  set(VCPKG_ROOT $ENV{VCPKG_ROOT})
endif()

if(VCPKG_ROOT)
  include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif()

set(OpenGL_GL_PREFERENCE "GLVND")

add_subdirectory(deps)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)

if(UNIX)
  find_library(FREETYPE_LIB freetype)
  find_library(PNG_LIB png)
  find_library(Z_LIB z)
  find_library(BZ2_LIB bz2)
  if(NOT FREETYPE_LIB)
    message(FATAL_ERROR "freetype not found")
  endif()
  if(NOT PNG_LIB)
    message(FATAL_ERROR "png not found")
  endif()
  if(NOT Z_LIB)
    message(FATAL_ERROR "z not found")
  endif()
  if(NOT BZ2_LIB)
    message(FATAL_ERROR "bz2 not found")
  endif()
  set(EXTRA_LIBS ${FREETYPE_LIB} ${PNG_LIB} ${Z_LIB} ${BZ2_LIB} unofficial::brotli::brotlidec)
endif()

include_directories(core ui)

set(CMAKE_CXX_STANDARD 17)

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
   $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
  $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_image::SDL2_ttf-static>
  ${EXTRA_LIBS}
  kst
  OpenGL::GL)

add_library(glider-ui STATIC ${UI_FILES})
target_link_libraries(glider-ui glider-core)

add_subdirectory(tests)

target_include_directories(glider-core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
)

target_include_directories(glider-ui PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
