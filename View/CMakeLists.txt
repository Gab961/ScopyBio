file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(View ${SRC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

FIND_PACKAGE("jsoncpp")

find_package(Qt5 COMPONENTS Widgets Core)

target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (View Controler ${CONAN_LIBS} Qt5::Widgets Qt5::Core)
