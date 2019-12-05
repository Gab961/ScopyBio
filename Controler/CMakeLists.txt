file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Controler ${SRC})

FIND_PACKAGE("jsoncpp")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

target_include_directories (Controler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries (Controler Model ${CONAN_LIBS} Qt5::Widgets)


target_include_directories (Controler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries (Controler jsoncpp boost_filesystem ${CONAN_LIBS} Qt5::Widgets)
