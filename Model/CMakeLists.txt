file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Model ${SRC})


FIND_PACKAGE("jsoncpp")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

target_include_directories (Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
