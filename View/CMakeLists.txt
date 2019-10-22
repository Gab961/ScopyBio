file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(View ${SRC})

target_include_directories (View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
