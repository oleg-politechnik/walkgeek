/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/waveplayer.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   I2S audio program
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "player.h"
#include "wav_decoder.h"
#include <string.h>
#include "mediafile.h"
#include "decoder.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  LittleEndian,
  BigEndian
} Endianness;

typedef struct
{
  uint32_t RIFFchunksize;
  uint16_t FormatTag;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
  uint32_t DataSize;
} WAVE_FormatTypeDef;

typedef enum
{
  Valid_WAVE_File = 0,
  Unvalid_RIFF_ID,
  Unvalid_WAVE_Format,
  Unvalid_FormatChunk_ID,
  Unsupporetd_FormatTag,
  Unsupporetd_Number_Of_Channel,
  Unsupporetd_Sample_Rate,
  Unsupporetd_Bits_Per_Sample,
  Unvalid_DataChunk_ID,
  Unsupporetd_ExtraFormatBytes,
  Unvalid_FactChunk_ID
} ErrorCode;

/* Private define ------------------------------------------------------------*/
#define  CHUNK_ID                            0x52494646  /* correspond to the letters 'RIFF' */
#define  FILE_FORMAT                         0x57415645  /* correspond to the letters 'WAVE' */
#define  FORMAT_ID                           0x666D7420  /* correspond to the letters 'fmt ' */
#define  DATA_ID                             0x64617461  /* correspond to the letters 'data' */
#define  FACT_ID                             0x66616374  /* correspond to the letters 'fact' */
#define  WAVE_FORMAT_PCM                     0x01
#define  FORMAT_CHNUK_SIZE                   0x10
#define  CHANNEL_MONO                        0x01
#define  CHANNEL_STEREO                      0x02
#define  SAMPLE_RATE_8000                    8000
#define  SAMPLE_RATE_11025                   11025
#define  SAMPLE_RATE_22050                   22050
#define  SAMPLE_RATE_44100                   44100
#define  BITS_PER_SAMPLE_8                   8
#define  BITS_PER_SAMPLE_16                  16

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
WAVE_FormatTypeDef WAVE_Format;
u32 SpeechDataOffset;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

FuncResult WAV_FastFileCheck(const char *fname)
{
  return MediaFile_CheckExtension(fname, "wav");
}



/**
 * @brief  Reads a number of bytes from the SPI Flash and reorder them in Big
 *         or little endian.
 * @param  NbrOfBytes: number of bytes to read.
 *         This parameter must be a number between 1 and 4.
 * @param  ReadAddr: external memory address to read from.
 * @param  Endians: specifies the bytes endianness.
 *         This parameter can be one of the following values:
 *             - LittleEndian
 *             - BigEndian
 * @retval Bytes read from the SPI Flash.
 */
uint32_t ReadUnit(uint8_t *buffer, uint8_t idx, uint8_t NbrOfBytes,
        Endianness BytesFormat)
{
  uint32_t index = 0;
  uint32_t temp = 0;

  for (index = 0; index < NbrOfBytes; index++)
  {
    temp |= buffer[idx + index] << (index * 8);
  }

  if (BytesFormat == BigEndian)
  {
    temp = __REV(temp);
  }
  return temp;
}

/**
 * @brief  Checks the format of the .WAV file and gets information about
 *   the audio format. This is done by reading the value of a
 *   number of parameters stored in the file header and comparing
 *   these to the values expected authenticates the format of a
 *   standard .WAV  file (44 bytes will be read). If  it is a valid
 *   .WAV file format, it continues reading the header to determine
 *   the  audio format such as the sample rate and the sampled data
 *   size. If the audio format is supported by this application,
 *   it retrieves the audio format in WAVE_Format structure and
 *   returns a zero value. Otherwise the function fails and the
 *   return value is nonzero.In this case, the return value specifies
 *   the cause of  the function fails. The error codes that can be
 *   returned by this function are declared in the header file->
 * @param  None
 * @retval Zero value if the function succeed, otherwise it return
 *         a nonzero value which specifies the error code.
 */
static ErrorCode WavePlayer_WaveParsing(MediaFile_Typedef *mfile)
{
  uint32_t temp = 0x00;
  uint32_t extraformatbytes = 0;

  MF_EXEC(MediaFile_FillFromFile(mfile, 0));

  /* Read chunkID, must be 'RIFF' */
  temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 0, 4, BigEndian);
  if (temp != CHUNK_ID)
  {
    return (Unvalid_RIFF_ID);
  }

  /* Read the file length */
  WAVE_Format.RIFFchunksize = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 4, 4,
          LittleEndian);

  /* Read the file format, must be 'WAVE' */
  temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 8, 4, BigEndian);
  if (temp != FILE_FORMAT)
  {
    return (Unvalid_WAVE_Format);
  }

  /* Read the format chunk, must be'fmt ' */
  temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 12, 4, BigEndian);
  if (temp != FORMAT_ID)
  {
    return (Unvalid_FormatChunk_ID);
  }
  /* Read the length of the 'fmt' data, must be 0x10 -------------------------*/
  temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 16, 4, LittleEndian);
  if (temp != 0x10)
  {
    extraformatbytes = 1;
  }
  /* Read the audio format, must be 0x01 (PCM) */
  WAVE_Format.FormatTag
          = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 20, 2, LittleEndian);
  if (WAVE_Format.FormatTag != WAVE_FORMAT_PCM)
  {
    return (Unsupporetd_FormatTag);
  }

  /* Read the number of channels, must be 0x01 (Mono) or 0x02 (Stereo) */
  WAVE_Format.NumChannels = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 22, 2,
          LittleEndian);

  /* Read the Sample Rate */
  WAVE_Format.SampleRate = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 24, 4,
          LittleEndian);

  /* Read the Byte Rate */
  WAVE_Format.ByteRate = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 28, 4, LittleEndian);

  /* Read the block alignment */
  WAVE_Format.BlockAlign = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 32, 2,
          LittleEndian);

  /* Read the number of bits per sample */
  WAVE_Format.BitsPerSample = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 34, 2,
          LittleEndian);
  if (WAVE_Format.BitsPerSample != BITS_PER_SAMPLE_16)
  {
    return (Unsupporetd_Bits_Per_Sample);
  }
  SpeechDataOffset = 36;
  /* If there is Extra format bytes, these bytes will be defined in "Fact Chunk" */
  if (extraformatbytes == 1)
  {
    /* Read th Extra format bytes, must be 0x00 */
    temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 36, 2, LittleEndian);
    if (temp != 0x00)
    {
      return (Unsupporetd_ExtraFormatBytes);
    }
    /* Read the Fact chunk, must be 'fact' */
    temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 38, 4, BigEndian);
    if (temp != FACT_ID)
    {
      return (Unvalid_FactChunk_ID);
    }
    /* Read Fact chunk data Size */
    temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), 42, 4, LittleEndian);

    SpeechDataOffset += 10 + temp;
  }
  /* Read the Data chunk, must be 'data' */
  temp = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), SpeechDataOffset, 4, BigEndian);
  SpeechDataOffset += 4;
  if (temp != DATA_ID)
  {
    return (Unvalid_DataChunk_ID);
  }

  /* Read the number of sample data */
  WAVE_Format.DataSize = ReadUnit((uint8_t*) &FILE_BUF(mfile, 0), SpeechDataOffset, 4,
          LittleEndian);
  SpeechDataOffset += 4;
  mfile->data_start = SpeechDataOffset;
  return (Valid_WAVE_File);
}

FuncResult WAV_TryFile(MediaFile_Typedef *mfile)
{
  //EXEC_ERROR_STATUS(File_CheckExtension(file->"wav"));

  ErrorCode res = WavePlayer_WaveParsing(mfile);

  if (res == Valid_WAVE_File)
  {
    MF_EXEC(MediaFile_FillFromFile(mfile, mfile->data_start));

    mfile->meta.channel_count = WAVE_Format.NumChannels;

    mfile->framesize = 2 * mfile->meta.channel_count;//???

    mfile->meta.mstime_max = ((unsigned long long) 1000 * (WAVE_Format.DataSize))
            / (WAVE_Format.SampleRate * mfile->framesize);

    return FUNC_SUCCESS;
  }

  return FUNC_ERROR;
}

FuncResult WAV_Decode(MediaFile_Typedef *mfile, AudioBuffer_Typedef *audio_buf)
{
  //  if (audio_buf->size != 0)
  //    return FR_SUCCESS;
  MF_EXEC(MediaFile_ReFill(mfile));
  memcpy(audio_buf->data, &FILE_BUF(mfile, 0), 512 * 2);
  audio_buf->size = 512;
  audio_buf->sampling_freq = WAVE_Format.SampleRate;

  MF_EXEC(MediaFile_Seek(mfile, 512 * 2));

  AudioBuffer_MoveProducer();

  mfile->meta.mstime_curr = ((unsigned long long) 1000 * (mfile->file.fptr
          - mfile->data_start)) / (WAVE_Format.SampleRate * 2
          * mfile->meta.channel_count);

  //file->meta.bitrate = mp3FrameInfo.bitrate;
  //file->meta.channel_count = mp3FrameInfo.nChans;

  return FUNC_SUCCESS;
}

FuncResult WAV_Seek(MediaFile_Typedef *mfile, s32 msec)
{
//  //  if (audio_buf->size != 0)
//  //    return FR_SUCCESS;
//  MF_EXEC(MediaFile_FillAtLeast(512 * 2));
//  memcpy(audio_buf->data, &FILE_BUF(mfile, 0), 512 * 2);
//  audio_buf->size = 512;
//  audio_buf->sampling_freq = WAVE_Format.SampleRate;
//
//  MF_EXEC(MediaFile_Seek(512 * 2, 0));
//
//  audio_buffer_move_producer();
//
//  file->meta.mstime_curr = ((unsigned long long) 1000 * (file->file.fptr
//          - file->data_start)) / (WAVE_Format.SampleRate * 2
//          * file->meta.channel_count);
//
//  //file->meta.bitrate = mp3FrameInfo.bitrate;
//  //file->meta.channel_count = mp3FrameInfo.nChans;

  return FUNC_SUCCESS;
}
