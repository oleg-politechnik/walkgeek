CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

if(NOT PLATFORM STREQUAL "SIMULATOR")
  include(gnu_toolchain.cmake)
endif()

PROJECT(walkgeek C ASM)

include(flags.cmake)

include_directories(
  include
  lib
  lib/fat_fs
  lib/mp3-fixpt-helix/pub
  lib/minIni
  lib/opus/include
  lib/freertos/include
)

add_definitions(-DUSE_FULL_ASSERT)

if(PROFILING)
  add_definitions(-DPROFILING)
  set(ENABLE_TRACE 1)
endif()

if(ENABLE_TRACE)
  add_definitions(-DENABLE_TRACE)
endif()

if(USE_MP3)
  add_definitions(-DUSE_MP3)
endif()

include(bsp/bsp.cmake)

add_subdirectory(lib)

set (SOURCES
    src/audio_buffer.c
#    src/player/wav_decoder.c
    src/player/opus_decoder.c
    src/player/player.c
    src/player/mediafile.c
    src/navigator.c
    src/nestedfilter.c
    src/ui/ui.c
    src/ui/player_ui.c
    src/ui/usb_ui.c
    src/usbd.c
    
    main.c
)

if(HAS_BATTERY)
  set (SOURCES ${SOURCES}
    src/powermanager.c
  )
endif()

IF(USE_MP3)
  set (SOURCES ${SOURCES}
      src/player/mp3_decoder.c
  )
endif()

add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES} ${CSP_SOURCES} ${BSP_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}.elf lib ${LIBRARIES})

add_custom_target(${CMAKE_PROJECT_NAME}.hex DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex)
add_custom_target(${CMAKE_PROJECT_NAME}.bin DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)
add_custom_target(${CMAKE_PROJECT_NAME}.dis DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${CMAKE_OBJDUMP} -dDsS ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.dis)
