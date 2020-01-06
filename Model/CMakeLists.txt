file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Model ${SRC})


FIND_PACKAGE("jsoncpp")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets Core)

target_include_directories (Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries (Model Controler jsoncpp ${CONAN_LIBS} Qt5::Widgets Qt5::Core)
