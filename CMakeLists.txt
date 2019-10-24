project(ScopyBio)

cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
add_compile_options(-Wall -Wpedantic)
endif()

#############

# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( " " )
  Message( FATAL_ERROR "Source and build  directories are the same.
 Create an empty build directory,
 change into it and re-invoke cmake")
endif()

# To use PKG_CHECK_MODULES to find some optional packages
find_package(PkgConfig)

#    Tell CMake where to leave executables
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

#Path of CImg.h file relative to this file path
set(CIMG_H_PATH ${PROJECT_SOURCE_DIR}/..)
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${CIMG_H_PATH} )


if(NOT WIN32)
  FIND_PACKAGE(X11)
  FIND_PACKAGE(Threads REQUIRED)
endif()

# #### End of additional libraries search ##########


### Configure Paths according to detected packages


if(NOT APPLE)
  if(NOT WIN32)
    if(X11_FOUND)
      SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_XSHM_CCFLAGS} ${CIMG_XRANDR_CCFLAGS}")
      SET(CONAN_LIBS ${CONAN_LIBS} Xext Xrandr)
    endif()
  endif(NOT WIN32)
endif(NOT APPLE)

if(X11_FOUND)
  link_directories(${X11_LIB_DIRS})
  include_directories(${X11_INCLUDE_DIR})
  SET( CONAN_LIBS ${CONAN_LIBS} ${X11_LIBRARIES} )
endif()

if (NOT WIN32)
  SET( CONAN_LIBS ${CONAN_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if( WIN32)
  SET( CONAN_LIBS  ${CONAN_LIBS}  gdi32 )
endif()

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")


########

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# ### CIMG related stuff
# Flags to enable fast image display, using the XSHM library.
SET(CIMG_XSHM_CCFLAGS  -Dcimg_use_xshm)

# Flags to enable screen mode switching, using the XRandr library.
SET(CIMG_XRANDR_CCFLAGS  -Dcimg_use_xrandr)

# Flags to enable native support for JPEG image files, using the JPEG library.
# ( http://www.ijg.org/ )
SET(CIMG_JPEG_CCFLAGS  -Dcimg_use_jpeg)

# Flags to enable native support for TIFF image files, using the TIFF library.
# ( http://www.libtiff.org/ )
SET(CIMG_TIFF_CCFLAGS  -Dcimg_use_tiff)

# Flags to enable native support for PNG image files, using the PNG library.
# ( http://www.libpng.org/ )
SET(CIMG_PNG_CCFLAGS  -Dcimg_use_png)

# Flags to enable native support for EXR image files, using the OpenEXR library.
# ( http://www.openexr.com/ )
SET(CIMG_OPENEXR_CCFLAGS  -Dcimg_use_openexr)

# Flags to enable native support for various video files, using the FFMPEG library.
# ( http://www.ffmpeg.org/ )
SET(CIMG_FFMPEG_CCFLAGS  -Dcimg_use_ffmpeg)

# Flags to enable native support of most classical image file formats, using the Magick++ library.
# ( http://www.imagemagick.org/Magick++/ )
SET(CIMG_MAGICK_CCFLAGS -Dcimg_use_magick)

# Flags to enable faster Discrete Fourier Transform computation, using the FFTW3 library
# ( http://www.fftw.org/ )
SET(CIMG_FFTW3_CCFLAGS  -Dcimg_use_fftw3)

aux_source_directory(. SRC_LIST)
add_subdirectory(Controler)
add_subdirectory(View)
add_subdirectory(Model)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries (${PROJECT_NAME}  ${CONAN_LIBS}  Qt5::Widgets Controler View Model)
