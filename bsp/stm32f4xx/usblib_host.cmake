add_definitions(-DUSE_HOST_MODE)

# CORE #########################################################################

INCLUDE_DIRECTORIES(
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_HOST_Library/Core/inc
)

SET(USB_LibraryCoreSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_HOST_Library/Core/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryCoreSrc_DIR}/usbh_core.c
    ${USB_LibraryCoreSrc_DIR}/usbh_hcs.c
    ${USB_LibraryCoreSrc_DIR}/usbh_ioreq.c
    ${USB_LibraryCoreSrc_DIR}/usbh_stdreq.c
)

# MSC ##########################################################################

INCLUDE_DIRECTORIES(
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_HOST_Library/Class/MSC/inc
)

SET(USB_LibraryMscSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_HOST_Library/Class/MSC/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_LibraryMscSrc_DIR}/usbh_msc_bot.c
    ${USB_LibraryMscSrc_DIR}/usbh_msc_core.c
    ${USB_LibraryMscSrc_DIR}/usbh_msc_fatfs.c
    ${USB_LibraryMscSrc_DIR}/usbh_msc_scsi.c
)

################################################################################
