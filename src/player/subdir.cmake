SET(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_LIST_DIR}/mp3_decoder.h
    ${CMAKE_CURRENT_LIST_DIR}/wav_decoder.h
)

SET(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/decoders.c
    ${CMAKE_CURRENT_LIST_DIR}/mp3_decoder.c
    ${CMAKE_CURRENT_LIST_DIR}/wav_decoder.c
    ${CMAKE_CURRENT_LIST_DIR}/mediafile.c
    ${CMAKE_CURRENT_LIST_DIR}/player.c
#    ${CMAKE_CURRENT_LIST_DIR}/playlist.c
    ${CMAKE_CURRENT_LIST_DIR}/opus_decoder.c
#    ${CMAKE_CURRENT_LIST_DIR}/opusdec.c
)
