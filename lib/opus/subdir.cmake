SET(OPUS_LIB_TYPE fltpt)
SET(OPUS_LIB opus-${OPUS_LIB_TYPE})

# Exporting includes and lib name
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/include)

SET(LIBRARIES ${LIBRARIES}
    ${OPUS_LIB_TYPE}
)

# OPUS library should be compiled with different optimization level, i.e. "-O2".
# CMake doesn't seem to allow different compile options for different
# sub-projects, so this lib is going to be an external project.

#todo: pass proc def from bsp. path to gnu_toolchan.cmake

INCLUDE(ExternalProject REQUIRED)
ExternalProject_Add(
     opus-${OPUS_LIB_TYPE}
     SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}
     CMAKE_ARGS
      -DTOOLCHAIN_CMAKE=${TOOLCHAIN_CMAKE}
      -DCPU_CMAKE=${CPU_CMAKE}
     BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${OPUS_LIB_TYPE}
     INSTALL_COMMAND ""
)

SET(DEPENDENCIES ${DEPENDENCIES}
    opus-${OPUS_LIB_TYPE}
)

ADD_LIBRARY(${OPUS_LIB_TYPE} STATIC IMPORTED)
SET_PROPERTY(TARGET ${OPUS_LIB_TYPE} PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/${OPUS_LIB_TYPE}/lib${OPUS_LIB_TYPE}.a)
