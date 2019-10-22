file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Controler ${SRC})

target_include_directories (Controler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
