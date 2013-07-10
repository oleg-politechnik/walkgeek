IF(NOT PLATFORM)
    SET(PLATFORM "N1100")
    MESSAGE(STATUS "No PLATFORM specified, using default: " ${PLATFORM})
ENDIF()

# right now only 1 target and only 1 architecture supported

if(PLATFORM STREQUAL "N1100")
  add_definitions(-DN1100)
  set (HAS_BATTERY 1)
  add_definitions(-DHAS_BATTERY)
  add_definitions(-DHAS_HEADSET)
  add_definitions(-DHAS_VIBRATOR)
  add_definitions(-DHAS_SDIO)
  set (USE_DEVICE_MODE 1)
  if(PROFILING)
    add_definitions(-DPROFILING)
  endif()
  if(NOT RPROG_OHM)
    MESSAGE(STATUS "No RPROG_OHM specified, using default: 2000")
    set (RPROG_OHM 2000)
  endif()
  add_definitions(-DRPROG_OHM=${RPROG_OHM})
elseif(PLATFORM STREQUAL "F4DISCOVERY")
  add_definitions(-DF4DISCOVERY)
  set (USE_HOST_MODE 1)
elseif(PLATFORM STREQUAL "SIMULATOR")
  add_definitions(-DSIMULATOR)
else()
  MESSAGE(FATAL_ERROR "Invalid PLATFORM = ${PLATFORM}, use "
                      "[N1100, F4DISCOVERY, SIMULATOR]")
endif()

###############################################################################

if (PLATFORM STREQUAL "N1100" OR
    PLATFORM STREQUAL "F4DISCOVERY")
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
  INCLUDE_DIRECTORIES(bsp/stm32f4xx/inc)
  
  set(CSP_SOURCES ${CSP_SOURCES}
      bsp/stm32f4xx/src/cpu.c
      bsp/stm32f4xx/src/stm32f4xx_it.c
      bsp/stm32f4xx/src/syscalls.c
      bsp/stm32f4xx/src/system_stm32f4xx.c
  )

  INCLUDE_DIRECTORIES(bsp/stm32f4_discovery)
  
  set(CSP_SOURCES ${CSP_SOURCES}
      bsp/freertos/GCC/ARM_CM3/port.c
  )
  
  INCLUDE_DIRECTORIES(bsp/freertos/GCC/ARM_CM3)
  
  set(BSP_SOURCES ${BSP_SOURCES}
      bsp/keypad.c
      bsp/stm32f4_discovery/audio_if.c
      bsp/stm32f4_discovery/bsp.c
      bsp/stm32f4_discovery/syscalls.c
      bsp/stm32f4_discovery/disp_1100.c
      bsp/stm32f4_discovery/stm32f4_discovery_audio_codec.c
  )
  
  if (PLATFORM STREQUAL "N1100")
    set(BSP_SOURCES ${BSP_SOURCES}
      bsp/stm32f4_discovery/stm324xg_eval_sdio_sd.c
      bsp/stm32f4_discovery/diskio_sdio.c
    )
  endif()
  
  if (PLATFORM STREQUAL "F4DISCOVERY")
    set(BSP_SOURCES ${BSP_SOURCES}
      bsp/stm32f4_discovery/stm32f4_discovery.c
    )
  endif()
  
  if(USE_DEVICE_MODE)
    set(CSP_SOURCES ${CSP_SOURCES}
      bsp/stm32f4xx/src/usbd_cdc_vcp.c
      bsp/stm32f4xx/src/usbd_cdc_core.c
      bsp/stm32f4xx/src/usbd_desc_msc.c
      bsp/stm32f4xx/src/usbd_desc_cdc.c
      bsp/stm32f4xx/src/usbd_storage_msd.c
      bsp/stm32f4xx/src/usbd_usr.c
      bsp/stm32f4xx/src/usbd_bsp.c
    )
  elseif(USE_HOST_MODE)
    set(CSP_SOURCES ${CSP_SOURCES}
      bsp/stm32f4xx/src/usbh_usr.c
      bsp/stm32f4xx/src/usbh_bsp.c
    )
    set (BSP_SOURCES ${BSP_SOURCES}
      bsp/stm32f4_discovery/fattime.c
    )
  endif()
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
