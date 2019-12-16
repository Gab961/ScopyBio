file(GLOB SRC
   "*.h"
   "*.cpp"
)

find_package(Qt5Widgets REQUIRED)
add_library(View ${SRC})

FIND_PACKAGE("jsoncpp")

target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (View Controler ${CONAN_LIBS} Qt5::Widgets)
