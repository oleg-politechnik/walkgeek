set (LIBS_FLAGS " -O3 ")

set (FAT_FS_SOURCES
    fat_fs/ff.c
    fat_fs/option/ccsbcs.c
)

set_source_files_properties(${FAT_FS_SOURCES} PROPERTIES COMPILE_FLAGS
    "-Wno-strict-aliasing ${LIBS_FLAGS}" )
    
set (LIBS_SOURCES
    minIni/minIni.c
    
    mm/mm_addfreechunk.c
    mm/mm_calloc.c
    mm/mm_free.c
    mm/mm_initialize.c
    mm/mm_mallinfo.c
    mm/mm_malloc.c
    mm/mm_memalign.c
    mm/mm_realloc.c
    mm/mm_sem.c
    mm/mm_shrinkchunk.c
    mm/mm_size2ndx.c
    mm/mm_user.c
    mm/mm_zalloc.c

    ogg/framing.c
)

if(USE_MP3)
  set (MP3_SOURCES
      mp3-fixpt-helix/real/stproc.c
      mp3-fixpt-helix/real/dct32.c
      mp3-fixpt-helix/real/dequant.c
      mp3-fixpt-helix/real/subband.c
      mp3-fixpt-helix/real/trigtabs_fixpt.c
      mp3-fixpt-helix/real/bitstream.c
      mp3-fixpt-helix/real/scalfact.c
      mp3-fixpt-helix/real/huffman.c
      mp3-fixpt-helix/real/buffers.c
      mp3-fixpt-helix/real/dqchan.c
      mp3-fixpt-helix/real/polyphase.c
      mp3-fixpt-helix/real/hufftabs.c
      mp3-fixpt-helix/real/imdct.c
      mp3-fixpt-helix/mp3dec.c
      mp3-fixpt-helix/mp3tabs.c
  )
  set_source_files_properties(${MP3_SOURCES} PROPERTIES COMPILE_FLAGS
      "-Wno-unused-but-set-variable ${LIBS_FLAGS}" )
endif()

#set (LIBS_SOURCES ${LIBS_SOURCES} ${MP3_SOURCES})

# Opus stuff
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DFIXED_POINT)
add_definitions(-DDISABLE_FLOAT_API)
add_definitions(-DCUSTOM_SUPPORT)

include_directories(BEFORE SYSTEM
  opus
  opus/include
  opus/celt
  opus/silk
)

set (LIBS_SOURCES ${LIBS_SOURCES}
  opus/celt/bands.c
  opus/celt/celt.c
  opus/celt/celt_lpc.c
  opus/celt/cwrs.c
  opus/celt/entcode.c
  opus/celt/entdec.c
  opus/celt/entenc.c
  opus/celt/kiss_fft.c
  opus/celt/laplace.c
  opus/celt/mathops.c
  opus/celt/mdct.c
  opus/celt/modes.c
  opus/celt/pitch.c
  opus/celt/quant_bands.c
  opus/celt/rate.c
  opus/celt/vq.c
  opus/silk/bwexpander_32.c
  opus/silk/bwexpander.c
  opus/silk/CNG.c
  opus/silk/code_signs.c
  opus/silk/dec_API.c
  opus/silk/decode_core.c
  opus/silk/decode_frame.c
  opus/silk/decode_indices.c
  opus/silk/decode_parameters.c
  opus/silk/decode_pitch.c
  opus/silk/decode_pulses.c
  opus/silk/decoder_set_fs.c
  opus/silk/gain_quant.c
  opus/silk/init_decoder.c
  opus/silk/log2lin.c
  opus/silk/lin2log.c
  opus/silk/LPC_analysis_filter.c
  opus/silk/LPC_inv_pred_gain.c
  opus/silk/NLSF2A.c
  opus/silk/NLSF_decode.c
  opus/silk/NLSF_stabilize.c
  opus/silk/NLSF_unpack.c
  opus/silk/NLSF_VQ_weights_laroia.c
  opus/silk/pitch_est_tables.c
  opus/silk/PLC.c
  opus/silk/resampler.c
  opus/silk/resampler_private_AR2.c
  opus/silk/resampler_private_down_FIR.c
  opus/silk/resampler_private_IIR_FIR.c
  opus/silk/resampler_private_up2_HQ.c
  opus/silk/resampler_rom.c
  opus/silk/shell_coder.c
  opus/silk/sort.c
  opus/silk/stereo_decode_pred.c
  opus/silk/stereo_MS_to_LR.c
  opus/silk/sum_sqr_shift.c
  opus/silk/table_LSF_cos.c
  opus/silk/tables_gain.c
  opus/silk/tables_LTP.c
  opus/silk/tables_NLSF_CB_NB_MB.c
  opus/silk/tables_NLSF_CB_WB.c
  opus/silk/tables_other.c
  opus/silk/tables_pitch_lag.c
  opus/silk/tables_pulses_per_block.c
  opus/src/opus_decoder.c
  opus/src/opus_header.c
)

set_source_files_properties(${LIBS_SOURCES} PROPERTIES COMPILE_FLAGS ${LIBS_FLAGS})

add_library(lib STATIC ${LIBS_SOURCES} ${MP3_SOURCES} ${FAT_FS_SOURCES})
