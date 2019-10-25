file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(View ${SRC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

FIND_Package("x11")
target_link_libraries(View x11)

target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
