# Note: always in Device mode
ADD_DEFINE(USE_USB_OTG_FS)
ADD_DEFINE(USE_DEVICE_MODE)
#ADD_DEFINE(USE_HOST_MODE)

# STM32_USB_OTG_Driver #########################################################
SET(USB_Device_LibraryOtgInc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_OTG_Driver/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryOtgInc_DIR}
)

SET(USBLIB_HEADERS ${USBLIB_HEADERS}
    ${USB_Device_LibraryOtgInc_DIR}/usb_bsp.h
#    ${USB_Device_LibraryOtgInc_DIR}/usb_conf_template.h
    ${USB_Device_LibraryOtgInc_DIR}/usb_core.h
    ${USB_Device_LibraryOtgInc_DIR}/usb_dcd.h
    ${USB_Device_LibraryOtgInc_DIR}/usb_dcd_int.h
    ${USB_Device_LibraryOtgInc_DIR}/usb_defines.h
#    ${USB_Device_LibraryOtgInc_DIR}/usb_otg.h
    ${USB_Device_LibraryOtgInc_DIR}/usb_regs.h
)

#

SET(USB_Device_LibraryOtgSrc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_OTG_Driver/src
)

SET(USBLIB_SOURCES ${USBLIB_SOURCES}
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
#    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Class/audio/inc
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
#    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Class/audio/src
#)
#
#SET(USBLIB_SOURCES ${USBLIB_SOURCES}
#    ${USB_Device_LibraryAudioSrc_DIR}/usbd_audio_core.c
#)

# MSC ##########################################################################

SET(USB_Device_LibraryMscInc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryMscInc_DIR}
)

SET(USBLIB_HEADERS ${USBLIB_HEADERS}
    ${USB_Device_LibraryMscInc_DIR}/usbd_msc_bot.h
    ${USB_Device_LibraryMscInc_DIR}/usbd_msc_data.h
    ${USB_Device_LibraryMscInc_DIR}/usbd_msc_scsi.h
    ${USB_Device_LibraryMscInc_DIR}/usbd_msc_core.h
    ${USB_Device_LibraryMscInc_DIR}/usbd_msc_mem.h
)

#

SET(USB_Device_LibraryMscSrc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Class/msc/src
)

SET(USBLIB_SOURCES ${USBLIB_SOURCES}
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_core.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_scsi.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_bot.c
    ${USB_Device_LibraryMscSrc_DIR}/usbd_msc_data.c
)

# Core #########################################################################

SET(USB_Device_LibraryCoreInc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Core/inc
)

INCLUDE_DIRECTORIES(
    ${USB_Device_LibraryCoreInc_DIR}
)

SET(USBLIB_HEADERS ${USBLIB_HEADERS}
    ${USB_Device_LibraryCoreInc_DIR}/usbd_def.h
    ${USB_Device_LibraryCoreInc_DIR}/usbd_req.h
    ${USB_Device_LibraryCoreInc_DIR}/usbd_core.h
    ${USB_Device_LibraryCoreInc_DIR}/usbd_ioreq.h
    ${USB_Device_LibraryCoreInc_DIR}/usbd_usr.h
)

#

SET(USB_Device_LibraryCoreSrc_DIR
    ${STM32_USBLib_DIR}/Libraries/STM32_USB_Device_Library/Core/src
)

SET(USBLIB_SOURCES ${USBLIB_SOURCES}
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_core.c
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_ioreq.c
    ${USB_Device_LibraryCoreSrc_DIR}/usbd_req.c
)

################################################################################

SET(USBLIB_NAME usblib_stm32f4xx)
ADD_LIBRARY(${USBLIB_NAME} STATIC ${USBLIB_SOURCES} ${USBLIB_HEADERS})
SET(LIBRARIES ${LIBRARIES}
    ${USBLIB_NAME}
)
