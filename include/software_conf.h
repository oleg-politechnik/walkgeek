/*
 * software_conf.h
 *
 * Copyright (c) 2012, Oleg Tsaregorodtsev
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOFTWARE_CONF_H_
#define SOFTWARE_CONF_H_

/* Software features */
#define PLAYER_DEFAULT_VOLUME               20
#define PLAYER_INI_FILE                     "0:/player.ini"

#define NAVIGATOR_MAX_NESTING_LEVEL         10

#define SD_BLOCK_SIZE                       512

#define USBD_MSC_SPEED_MPS                  4

/* Speeds and delays */
#define HZ                                  1000

/* Memory */
#define FILE_BUFFER_SIZE                    2048
#define AUDIO_BUFFER_MAX_SIZE               2500
#define AUDIO_BUFFER_COUNT                  4

/* CDC buf size */
#define APP_RX_DATA_SIZE                    8192

//#define MINOGG_GRANULEPOS_CACHE

#ifdef SIMULATOR
# undef ENABLE_TRACE
# define ENABLE_TRACE                        1
#endif

#endif /* SOFTWARE_CONF_H_ */
