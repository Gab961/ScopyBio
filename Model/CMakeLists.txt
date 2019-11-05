file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Model ${SRC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

FIND_PACKAGE("jsoncpp")

target_include_directories (Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries (Model jsoncpp ${CONAN_LIBS} Qt5::Widgets)
