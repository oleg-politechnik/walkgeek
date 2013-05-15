# Note: always in Device mode

add_definitions(-DUSE_USB_OTG_FS)
add_definitions(-DUSE_DEVICE_MODE)
#ADD_DEFINE(USE_HOST_MODE)

# STM32_USB_OTG_Driver #########################################################
SET(USB_Device_LibraryOtgInc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_OTG_Driver/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryOtgInc_DIR}
)
SET(USB_Device_LibraryOtgSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_OTG_Driver/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_Device_LibraryOtgSrc_DIR}/usb_core.c
    ${USB_Device_LibraryOtgSrc_DIR}/usb_dcd.c
    ${USB_Device_LibraryOtgSrc_DIR}/usb_dcd_int.c
#    ${USB_Device_LibraryOtgSrc_DIR}/usb_hcd.c
#    ${USB_Device_LibraryOtgSrc_DIR}/usb_hcd_int.c
#    ${USB_Device_LibraryOtgSrc_DIR}/usb_otg.c
)

# STM32_USB_Device_Library #####################################################
# Audio ########################################################################
#SET(USB_Device_LibraryAudioInc_DIR
#    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/audio/inc
#)
#
#INCLUDE_DIRECTORIES(
#    ${USB_Device_LibraryAudioInc_DIR}
#)
#
#SET(USBLIB_HEADERS ${USBLIB_HEADERS}
#    ${USB_Device_LibraryAudioInc_DIR}/usbd_audio_core.h
#    ${USB_Device_LibraryAudioInc_DIR}/usbd_audio_out_if.h
#)
#
##
#
#SET(USB_Device_LibraryAudioSrc_DIR
#    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/audio/src
#)
#
#SET(USBLIB_SOURCES ${USBLIB_SOURCES}
#    ${USB_Device_LibraryAudioSrc_DIR}/usbd_audio_core.c
#)

# MSC ##########################################################################

SET(USB_Device_LibraryMscInc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryMscInc_DIR}
)

SET(USB_Device_LibraryMscSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_core.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_scsi.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_bot.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_data.c
)

# Core #########################################################################

SET(USB_Device_LibraryCoreInc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Core/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryCoreInc_DIR}
)

#

SET(USB_Device_LibraryCoreSrc_DIR
    ${STM32_USBSTDLib_DIR}/Libraries/STM32_USB_Device_Library/Core/src
)

SET(CSP_SOURCES ${CSP_SOURCES}
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_core.c
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_ioreq.c
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_req.c
)

################################################################################