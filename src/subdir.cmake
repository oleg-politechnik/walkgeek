SET(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/audio_buffer.c
    ${CMAKE_CURRENT_LIST_DIR}/audio_if.c
    ${CMAKE_CURRENT_LIST_DIR}/keypad.c
    ${CMAKE_CURRENT_LIST_DIR}/powermanager.c
    ${CMAKE_CURRENT_LIST_DIR}/scheduler.c
    ${CMAKE_CURRENT_LIST_DIR}/system.c
    ${CMAKE_CURRENT_LIST_DIR}/ui.c
    ${CMAKE_CURRENT_LIST_DIR}/usbd.c
    ${CMAKE_CURRENT_LIST_DIR}/nestedfilter.c
)

INCLUDE_SUBDIR(player)
