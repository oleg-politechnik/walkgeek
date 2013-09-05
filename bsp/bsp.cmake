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
else()
  MESSAGE(FATAL_ERROR "Invalid PLATFORM = ${PLATFORM}, use "
                      "[N1100, F4DISCOVERY]")
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
      bsp/freertos/GCC/ARM_CM4F/port.c
  )
  
  add_definitions(-D GCC_ARMCM3)
  add_definitions(-D inline=)
  add_definitions("-D PACK_STRUCT_END=__attribute\\(\\(packed\\)\\)" )
  add_definitions("-D ALIGN_STRUCT_END=__attribute\\(\\(aligned\\(4\\)\\)\\)")
  
  INCLUDE_DIRECTORIES(bsp/freertos/GCC/ARM_CM4F)
    
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
    add_definitions(-DUSE_DEVICE_MODE)
  elseif(USE_HOST_MODE)
    set(CSP_SOURCES ${CSP_SOURCES}
      bsp/stm32f4xx/src/usbh_usr.c
      bsp/stm32f4xx/src/usbh_bsp.c
    )
    set (BSP_SOURCES ${BSP_SOURCES}
      bsp/stm32f4_discovery/fattime.c
    )
    add_definitions(-DUSE_HOST_MODE)
  endif()
endif()
