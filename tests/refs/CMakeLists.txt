cmake_minimum_required(VERSION 3.10)

add_executable(refstest test.cpp)
if(MSVC)
  set_target_properties(refstest PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif()

target_link_libraries(refstest glider-core)
