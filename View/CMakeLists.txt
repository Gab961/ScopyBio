file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(View ${SRC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
