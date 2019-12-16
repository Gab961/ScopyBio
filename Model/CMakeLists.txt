file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Model ${SRC})

FIND_PACKAGE("jsoncpp")

target_include_directories (Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (Model Controler ${CONAN_LIBS} Qt5::Widgets)
