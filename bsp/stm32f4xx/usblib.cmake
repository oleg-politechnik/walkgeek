add_definitions(-DUSE_USB_OTG_FS)

# STM32_USB_OTG_Driver #########################################################
SET(USB_LibraryOtgInc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_OTG_Driver/inc
)

INCLUDE_DIRECTORIES(
    ${USB_LibraryOtgInc_DIR}
)
SET(USB_LibraryOtgSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_OTG_Driver/src
)

if(USE_DEVICE_MODE)
  SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryOtgSrc_DIR}/usb_core.c
    ${USB_LibraryOtgSrc_DIR}/usb_dcd.c
    ${USB_LibraryOtgSrc_DIR}/usb_dcd_int.c
  )
elseif(USE_HOST_MODE)
  SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryOtgSrc_DIR}/usb_core.c
    ${USB_LibraryOtgSrc_DIR}/usb_hcd.c
    ${USB_LibraryOtgSrc_DIR}/usb_hcd_int.c
  )
endif()

################################################################################

if(USE_DEVICE_MODE)
  include(bsp/stm32f4xx/usblib_device.cmake)
endif()

if(USE_HOST_MODE)
  include(bsp/stm32f4xx/usblib_host.cmake)
endif()
