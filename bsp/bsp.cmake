IF(NOT PLATFORM)
    SET(PLATFORM "NOKIA1100")
    MESSAGE(STATUS "No PLATFORM specified, using default: " ${PLATFORM})
ENDIF()

# right now only 1 target and only 1 architecture supported

if(PLATFORM STREQUAL "NOKIA1100")
  add_definitions(-DNOKIA1100)
elseif(PLATFORM STREQUAL "STM32F4DISCOVERY")
  add_definitions(-DSTM32F4DISCOVERY)
elseif(PLATFORM STREQUAL "SIMULATOR")
  add_definitions(-DSIMULATOR)
else()
  MESSAGE(FATAL_ERROR "Invalid PLATFORM = ${PLATFORM}, use "
                      "[NOKIA1100, STM32F4DISCOVERY, SIMULATOR]")
endif()

###############################################################################

if (PLATFORM STREQUAL "NOKIA1100" OR
    PLATFORM STREQUAL "STM32F4DISCOVERY")
  IF(NOT STM32_USBSTDLib_DIR)
      SET(STM32_USBSTDLib_DIR "${CMAKE_SOURCE_DIR}/bsp/3rd_party/STM32_USB-Host-Device_Lib_V2.1.0")
      MESSAGE(STATUS "No STM32_USBSTDLib_DIR specified, using default: " ${STM32_USBSTDLib_DIR})
  ENDIF()
  
  include(bsp/stm32f4xx/cmsis.cmake)
  include(bsp/stm32f4xx/stdperiph.cmake)
  include(bsp/stm32f4xx/usblib.cmake)
  
  include(bsp/stm32f4xx/cpu.cmake)
  
  STM32F4XX_SET_PARAMS("1024K" "128K")
  SET(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_BINARY_DIR}/stm32_flash.ld -Wl,-Map -Wl,${CMAKE_PROJECT_NAME}.map -mthumb -mcpu=cortex-m4" CACHE INTERNAL "exe link flags")
  # -Wl,-nostartfiles 
  INCLUDE_DIRECTORIES(bsp/stm32f4xx/inc)
  
  set (CSP_SOURCES ${CSP_SOURCES}
      bsp/stm32f4xx/src/cpu.c
      bsp/stm32f4xx/src/stm32f4xx_it.c
      bsp/stm32f4xx/src/syscalls.c
      bsp/stm32f4xx/src/usbd_cdc_vcp.c
      bsp/stm32f4xx/src/usbd_cdc_core.c
      bsp/stm32f4xx/src/usbd_desc_msc.c
      bsp/stm32f4xx/src/usbd_desc_cdc.c
      bsp/stm32f4xx/src/usbd_storage_msd.c
      bsp/stm32f4xx/src/system_stm32f4xx.c
      bsp/stm32f4xx/src/usbd_usr.c
      bsp/stm32f4xx/src/usb_bsp.c
  )
  
  INCLUDE_DIRECTORIES(bsp/stm32f4_discovery)
  set (BSP_SOURCES ${BSP_SOURCES}
      bsp/keypad.c
      bsp/stm32f4_discovery/audio_if.c
      bsp/stm32f4_discovery/bsp.c
      bsp/stm32f4_discovery/syscalls.c
      bsp/stm32f4_discovery/diskio_sdio.c
      bsp/stm32f4_discovery/disp_1100.c
      bsp/stm32f4_discovery/stm32f4_discovery_audio_codec.c
      bsp/stm32f4_discovery/stm324xg_eval_sdio_sd.c
  #    ${CMAKE_CURRENT_LIST_DIR}/stm32f4_discovery_lis302dl.c
  )
endif()

if(PLATFORM STREQUAL "SIMULATOR")
  INCLUDE_DIRECTORIES(bsp/simulator)

  if(NOT SD_CARD_FILE)
    MESSAGE(FATAL_ERROR "You need to define SD_CARD_FILE")
  endif()
  
  add_definitions(-DSD_CARD_FILE="${SD_CARD_FILE}")

  set (BSP_SOURCES ${BSP_SOURCES}
      bsp/simulator/bsp.c
      bsp/simulator/diskio_sdio.c
  )
  
  set (LIBRARIES ${LIBRARIES}
      pthread
  )
endif()
