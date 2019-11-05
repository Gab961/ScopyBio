file(GLOB SRC
   "*.h"
   "*.cpp"
)

find_package(Qt5Widgets REQUIRED)
add_library(View ${SRC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

FIND_PACKAGE("jsoncpp")

target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (View jsoncpp ${CONAN_LIBS} Qt5::Widgets)
