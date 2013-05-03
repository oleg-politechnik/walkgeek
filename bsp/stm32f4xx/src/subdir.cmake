INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR})

SET (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/cpu.c
    ${CMAKE_CURRENT_LIST_DIR}/stm32f4xx_it.c
    ${CMAKE_CURRENT_LIST_DIR}/syscalls.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_cdc_vcp.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_cdc_core.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_desc_msc.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_desc_cdc.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_storage_msd.c
    ${CMAKE_CURRENT_LIST_DIR}/system_stm32f4xx.c
    ${CMAKE_CURRENT_LIST_DIR}/mm_user.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd_usr.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_bsp.c
)
