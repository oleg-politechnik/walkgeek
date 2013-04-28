IF(NOT TOOLCHAIN_CMAKE)
    MESSAGE(SEND_ERROR "ERROR: No TOOLCHAIN_CMAKE specified!")
ENDIF()

INCLUDE(${TOOLCHAIN_CMAKE})

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
ENABLE_LANGUAGE(ASM)

PROJECT(fixpt-helix)

SET(OPTIMIZATION_LEVEL 2)

IF(NOT CPU_CMAKE)
    MESSAGE(SEND_ERROR "ERROR: No CPU_CMAKE specified!")
ENDIF()

INCLUDE(${CPU_CMAKE})

INCLUDE_DIRECTORIES(real)
INCLUDE_DIRECTORIES(pub)

SET(SOURCES 
    mp3dec.c
    real/stproc.c
    real/dct32.c
    real/dequant.c
    real/subband.c
    real/trigtabs_fixpt.c
    real/bitstream.c
    real/scalfact.c
    real/huffman.c
    real/buffers.c
    real/dqchan.c
    real/polyphase.c
    real/hufftabs.c
    real/imdct.c
    mp3tabs.c
)

ADD_LIBRARY(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})
