INCLUDE_SUBDIR(fixpt-helix)

# MP3 library should be compiled with different optimization level, i.e. "-O2".
# CMake doesn't seem to allow different compile options for different
# sub-projects, so this lib is going to be an external project.

#todo: pass proc def from bsp. path to gnu_toolchan.cmake

INCLUDE(ExternalProject REQUIRED)
ExternalProject_Add(
     mp3-${MP3_LIB_TYPE}
     SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${MP3_LIB_TYPE}
     CMAKE_ARGS
      -DTOOLCHAIN_CMAKE=${TOOLCHAIN_CMAKE}
      -DCPU_CMAKE=${CPU_CMAKE}
     BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${MP3_LIB_TYPE}
     INSTALL_COMMAND ""
)

SET(DEPENDENCIES ${DEPENDENCIES}
    mp3-${MP3_LIB_TYPE}
)