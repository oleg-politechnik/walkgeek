add_definitions(-DUSE_DEVICE_MODE)

# CORE #########################################################################

INCLUDE_DIRECTORIES(
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Core/inc
)

SET(USB_LibraryCoreSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Core/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryCoreSrc_DIR}/usbd_core.c
    ${USB_LibraryCoreSrc_DIR}/usbd_ioreq.c
    ${USB_LibraryCoreSrc_DIR}/usbd_req.c
)

# MSC ##########################################################################

INCLUDE_DIRECTORIES(
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/inc
)

SET(USB_LibraryMscSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryMscSrc_DIR}/usbd_msc_core.c
    ${USB_LibraryMscSrc_DIR}/usbd_msc_scsi.c
    ${USB_LibraryMscSrc_DIR}/usbd_msc_bot.c
    ${USB_LibraryMscSrc_DIR}/usbd_msc_data.c
)

################################################################################
