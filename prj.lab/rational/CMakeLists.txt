add_library(rational rational.hpp rational.cpp)
set_property(TARGET rational PROPERTY CXX_STANDARD 20)

target_include_directories(rational PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS rational)
