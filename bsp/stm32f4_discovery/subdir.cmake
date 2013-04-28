INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR})

SET (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/bsp.c
    ${CMAKE_CURRENT_LIST_DIR}/diskio_sdio.c
    ${CMAKE_CURRENT_LIST_DIR}/disp_1100.c
    ${CMAKE_CURRENT_LIST_DIR}/keyboard.c
    ${CMAKE_CURRENT_LIST_DIR}/stm32f4_discovery_audio_codec.c
    ${CMAKE_CURRENT_LIST_DIR}/stm324xg_eval_sdio_sd.c
#    ${CMAKE_CURRENT_LIST_DIR}/stm32f4_discovery_lis302dl.c
)