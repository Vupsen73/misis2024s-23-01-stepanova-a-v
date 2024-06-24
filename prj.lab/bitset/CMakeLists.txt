add_library(bitset bitset.hpp bitset.cpp)

set_property(TARGET bitset PROPERTY CXX_STANDARD 20)

target_include_directories(bitset PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS bitset)
