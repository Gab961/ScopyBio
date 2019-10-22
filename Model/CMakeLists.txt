file(GLOB SRC
   "*.h"
   "*.cpp"
)

add_library(Model ${SRC})

target_include_directories (Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
