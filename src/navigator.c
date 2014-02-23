/*
 * navigator.c
 *
 * Copyright (c) 2013, Oleg Tsaregorodtsev
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "navigator.h"
#include "assert.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//static void Navigator_NextFileCurrentDir(NavigatorContext_Typedef *ctx);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static FATFS fatfs;
static FRESULT res;

static bool online;

static char root[] = "0:";

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Navigator_Init(void)
{
  f_mount(0, &fatfs);
}

static int NumEntries(char *dir_path)
{
  int ret = 0;

  DIR dir;

  char buf[256];
  FILINFO file_info;
  file_info.lfsize = 0;

  char *name = 0;

  res = f_opendir(&dir, dir_path);
  if (res != FR_OK)
  {
    trace("navigator: error opening %s (%u)\n", dir_path, res);
    return 0;
  }

  res = f_readdir(&dir, 0);
  if (res != FR_OK)
  {
    trace("navigator: error opening %s (%u)\n", dir_path, res);
    return 0;
  }

  while (1)
  {
    res = f_readdir(&dir, &file_info);
    if (res != FR_OK)
    {
      trace("navigator: ERROR f_readdir(%s) -> %u\n", dir_path, res);
      return 0;
    }

    if (file_info.fname[0] == 0)
    {
      break;
    }

    ret++;
  }

  return ret;
}

void Navigator_ResetDir(NavigatorContext_Typedef *ctx)
{
  NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];

  ndir->dir_entry_ix_new = -1;
  ndir->dir_entry_prev_interesting_ix = -1;

  res = f_readdir(&ndir->dir, 0);
  if (res != FR_OK)
  {
    trace("navigator: error opening %s (%u)\n", ctx->dir_path, res);
    return;
  }
}

static void DirPosLastPlusOne(NavigatorContext_Typedef *ctx)
{
  NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];

  ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_new = ndir->dir_entry_ix_count-1;
}

static void OpenDir(NavigatorContext_Typedef *ctx, char *dir_path)
{
  NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];

  do
  {
    res = f_opendir(&ndir->dir, dir_path);
    if (res != FR_OK)
    {
      trace("navigator: not ready\n");
    }
  } while (res == FR_NOT_READY);

  if (res != FR_OK)
  {
    trace("navigator: error opening %s (%u)\n", dir_path, res);
    return;
  }

  Navigator_ResetDir(ctx);

  ndir->dir_entry_ix_count = NumEntries(ctx->dir_path);

  trace("navigator: ============= cd %s\n", ctx->dir_path);
}

bool Navigator_CdUp(NavigatorContext_Typedef *ctx)
{
  char *p;

  if (!ctx->dir_nesting_)
  {
    return false;
  }

  for (p = ctx->dir_path + strlen(ctx->dir_path); p > ctx->dir_path; p--)
  {
    if (*p == '/')
    {
      *p = 0;
      break;
    }
  }
  ctx->dir_nesting_--;

  trace("navigator: ============= cd %s\n", ctx->dir_path);

  return true;
}

static bool CdDown(NavigatorContext_Typedef *ctx)
{
  FILINFO *file_info = &(ctx->file_info_);
  char *dir_path = *(file_info->lfname) ? file_info->lfname : file_info->fname;

  if (!(file_info->fattrib & AM_DIR))
  {
    trace("navigator: Error: not a dir %s\n", dir_path);
    return false;
  }

  if (ctx->dir_nesting_ >= NAVIGATOR_MAX_NESTING_LEVEL)
  {
    trace("navigator: can't open dir %s/%s (max subdir level reached)\n", ctx->dir_path, dir_path);
    return false;
  }

  if (strlen(ctx->dir_path) + 1 + strlen(dir_path) + 1 > sizeof(ctx->dir_path))
  {
    trace("navigator: can't open dir %s/%s (path too long)\n", ctx->dir_path, dir_path);
    return false;
  }

  sprintf(ctx->dir_path + strlen(ctx->dir_path), "/%s", dir_path);
  ctx->dir_nesting_++;

  OpenDir(ctx, ctx->dir_path);
  /* TODO: no dir */
  if (res != FR_OK)
  {
    return false;
  }

  return true;
}

static int CheckSuffix(char *fname, char *suffixes_white_list[])
{
  assert_param(fname);

  char *ext;
  int suffix_ix = 0;

  while ((ext = suffixes_white_list[suffix_ix++]))
  {
    int len = strlen(fname);
    int ext_len = strlen(ext) + 1;
    const char *ext_begin = &fname[len - ext_len];

    if (len < ext_len)
    {
      continue;
    }

    if (ext_begin[0] != '.')
    {
      continue;
    }

    if (!strcasecmp(&ext_begin[1], ext))
    {
      return suffix_ix - 1;
    }
  }

  return -1;
}

bool Navigator_IsOnline(void)
{
  return (res == FR_OK);
}

void Navigator_InitRoot(NavigatorContext_Typedef *ctx,
        char *suffixes_white_list[])
{
  ctx->dir_nesting_ = 0;
  ctx->dir_path[0] = 0;

  ctx->suffixes_white_list_ = suffixes_white_list;

  ctx->file_info_.lfname = ctx->lfn_buf_;
  ctx->file_info_.lfsize = sizeof(ctx->lfn_buf_);

  memcpy(ctx->dir_path, root, sizeof(root));

  OpenDir(ctx, root);

  configASSERT(res == FR_OK);

  trace("navigator: init\n");
}

void Navigator_DeInit(void)
{
  f_mount(0, NULL);
  online = false; //todo var state
  trace("navigator: deinit\n");
}

bool Navigator_Cd(NavigatorContext_Typedef *ctx, char *path)
{
  DIR d;

  char path_cached[256];

  strncpy(path_cached, path, sizeof(path_cached));

  FILINFO fno;
  FRESULT fr = f_opendir(&d, path_cached);
  if (fr != FR_OK)
  {
    trace("navigator: jumping to %s failed\n", path);
    return false;
  }

  while (Navigator_CdUp(ctx))
    //todo find common ancestor
    ;

  Navigator_ResetDir(ctx);

  char dir_temp[256];
  char *dir_begin;
  char *dir_end;

  dir_begin = strchr(path_cached, '/');

  if (!dir_begin)
  {
    return Navigator_IsOnline();
  }

  dir_begin++;

  dir_end = strchr(dir_begin, '/');

  for (;;)
  {
    if (!dir_end)
    {
      dir_end = dir_begin + strlen(dir_begin);
    }

    if (!dir_begin[0])
      return true;

    assert_param((int) sizeof(dir_temp) > dir_end - dir_begin);

    memcpy(dir_temp, dir_begin, dir_end - dir_begin);
    dir_temp[dir_end - dir_begin] = 0;

    {
      FILINFO *file_info = &(ctx->file_info_);
      NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];
      char *name = 0;

      while (1)
      {
        res = f_readdir(&ndir->dir, file_info);
        if (res != FR_OK)
        {
          return false;
        }

        name = *(file_info->lfname) ? file_info->lfname : file_info->fname;

        if (name[0] == 0)
        {
          trace("navigator: ERROR Navigator_Cd rewinding reached the end \"%s\"\n", path);
          return false;
        }

        ndir->dir_entry_ix_new++;

        //if (name[0] == '.')
        //  continue; /* Ignore dot entry */

        if ((file_info->fattrib & AM_DIR) && (!strcmp(name, dir_temp)))
        {
          if (!CdDown(ctx))
          {
            //give up?
            while (Navigator_CdUp(ctx))
              ;

            return false;
          }
          break;
        }

        ndir->dir_entry_prev_interesting_ix++;
      }
    }

    if (dir_end == dir_begin + strlen(dir_begin))
      break;

    dir_begin = dir_end + 1;
    dir_end = strchr(dir_begin, '/');
  }

  return true;
}

bool Navigator_TryFile(NavigatorContext_Typedef *ctx, char *filename)
{
  //todo debug
  char filepath[512];

  ctx->fname = 0;

  snprintf(filepath, sizeof(filepath), "%s/%s", ctx->dir_path, filename);

  if (f_stat(filepath, &ctx->file_info_) != FR_OK || (ctx->file_info_.fattrib
          & AM_DIR))
  {
    trace("navigator: jumping to %s failed\n", filename);
    return false;
  }

  ctx->suffix_ix = CheckSuffix(filename, ctx->suffixes_white_list_);

  if (ctx->suffix_ix == -1)
  {
    return false;
  }

  {
    FILINFO *file_info = &(ctx->file_info_);
    NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];
    char *name = 0;

    while (1)
    {
      res = f_readdir(&ndir->dir, file_info);
      if (res != FR_OK)
      {
        return false;
      }

      name = *(file_info->lfname) ? file_info->lfname : file_info->fname;

      if (name[0] == 0)
      {
        trace("navigator: ERROR Navigator_TryFile rewinding reached the end\n");
        return false;
      }

      ndir->dir_entry_ix_new++;

      //if (name[0] == '.')
      //  continue; /* Ignore dot entry */

      if (strcmp(name, filename))
      {
        continue;
      }

      ctx->suffix_ix = CheckSuffix(name, ctx->suffixes_white_list_);

      if (ctx->suffix_ix != -1)
      {
        ctx->fname = name;

//        trace("file: %s/%s\n", ctx->dir_path, name);

        return true;
      }

      return false;
    }
  }

  configASSERT(!"Failed to open file");
  return false;
}

void Navigator_NextFile(NavigatorContext_Typedef *ctx)
{
  FILINFO *file_info = &(ctx->file_info_);
  NavigatorDir_Typedef *ndir;

  char *name = 0;

  ctx->fname = 0;

  while (1)
  {
    ndir = &ctx->dir_[ctx->dir_nesting_];

    res = f_readdir(&ndir->dir, file_info);
    if (res != FR_OK)
    {
      return;
    }

    ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_new;

    name = *(file_info->lfname) ? file_info->lfname : file_info->fname;

    if (name[0] == 0)
    {
      int prev_leaf_ix = ctx->dir_nesting_;
      for (int ix = ctx->dir_nesting_; ix >= 0; ix--)
      {
        if (ctx->dir_[ix].dir_entry_ix_new < (int) ctx->dir_[ix].dir_entry_ix_count - 1)
        {
          /*fixme debug*/
          for (int i = prev_leaf_ix; i > ix; i--)
          {
            Navigator_CdUp(ctx);
          }
          Navigator_NextFile(ctx);
          return;
        }
      }

      /* we are at the end */
      return;
    }

    ndir->dir_entry_ix_new++;

    //if (name[0] == '.')
    //  continue; /* Ignore dot entry */

    if (file_info->fattrib & AM_DIR)
    {
      if (!CdDown(ctx))
        return;

      continue;
    }

    ctx->suffix_ix = CheckSuffix(name, ctx->suffixes_white_list_);

    if (ctx->suffix_ix != -1)
    {
      ctx->fname = name;

//      trace("file: %s/%s\n", ctx->dir_path, name);

      return;
    }
  }
}

#if 0
static void Navigator_NextFileCurrentDir(NavigatorContext_Typedef *ctx)
{
  FILINFO *file_info = &(ctx->file_info_);
  NavigatorDir_Typedef *ndir;

  char *name = 0;

  ctx->fname = 0;

  while (1)
  {
    ndir = &ctx->dir_[ctx->dir_nesting_];

    res = f_readdir(&ndir->dir, file_info);
    if (res != FR_OK)
    {
      return;
    }

    name = *(file_info->lfname) ? file_info->lfname : file_info->fname;

    if (name[0] == 0)
    {
      return;
    }

    ndir->dir_entry_ix_new++;

    //if (name[0] == '.')
    //  continue; /* Ignore dot entry */

    if (file_info->fattrib & AM_DIR)
    {
      continue;
    }

    ctx->suffix_ix = CheckSuffix(name, ctx->suffixes_white_list_);

    if (ctx->suffix_ix != -1)
    {
      ctx->fname = name;

      return;
    }
  }
}
#endif

static void Navigator_PrevFileCurrentDir(NavigatorContext_Typedef *ctx)
{
  FILINFO *file_info = &(ctx->file_info_);
  NavigatorDir_Typedef *ndir = &ctx->dir_[ctx->dir_nesting_];
  char *name = 0;
  int new_ix;

  ctx->fname = 0;

  trace("   (i%d,%d)_%d\n",
          ndir->dir_entry_prev_interesting_ix, ndir->dir_entry_ix_new, ndir->dir_entry_ix_count
  );

  if (ndir->dir_entry_ix_new == 0 && ndir->dir_entry_prev_interesting_ix > 0)
  {
    Navigator_ResetDir(ctx);
  }

  if (ndir->dir_entry_ix_new < 0)
  {
    return;
  }

  while (1)
  {
    if (ndir->dir_entry_prev_interesting_ix > ndir->dir_entry_ix_new)
    {
      trace("navigator: WARNING ndir->dir_entry_prev_interesting_ix > ndir->dir_entry_ix (%d,%d)\n",
              ndir->dir_entry_prev_interesting_ix, ndir->dir_entry_ix_new);
      ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_new - 1;
    }

    if (ndir->dir_entry_prev_interesting_ix >= ndir->dir_entry_ix_count)
    {
      trace("navigator: WARNING ndir->dir_entry_prev_interesting_ix >= ndir->dir_entry_ix_count (%d,%d)\n",
              ndir->dir_entry_prev_interesting_ix, ndir->dir_entry_ix_count);
      ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_count - 1;
    }

    if (ndir->dir_entry_prev_interesting_ix < 0)
    {
      new_ix = ndir->dir_entry_ix_new;
    }
    else
    {
      new_ix = ndir->dir_entry_prev_interesting_ix + 1;
    }

    Navigator_ResetDir(ctx);

    while (new_ix-- > 0)
    {
      res = f_readdir(&ndir->dir, file_info);
      configASSERT(res == FR_OK);

      if (file_info->fname[0] == 0)
      {
      	configASSERT(!"navigator: dir EOF when rewinding");
      }

      ndir->dir_entry_ix_new++;

      //if (name[0] == '.')
      //  continue; /* Ignore dot entry */

      if (file_info->fattrib & AM_DIR)
      {
        if (new_ix > 0)
        {
          ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_new;
        }
        continue;
      }

      name = *(file_info->lfname) ? file_info->lfname : file_info->fname;

      if (CheckSuffix(name, ctx->suffixes_white_list_) != -1)
      {
        if (new_ix > 0)
        {
          ndir->dir_entry_prev_interesting_ix = ndir->dir_entry_ix_new;
        }
      }
    }

    trace("-> (i%d,%d)_%d\n",
            ndir->dir_entry_prev_interesting_ix, ndir->dir_entry_ix_new, ndir->dir_entry_ix_count
    );

    if (file_info->fattrib & AM_DIR)
    {
      return;
    }

    if (name)
    {
      ctx->suffix_ix = CheckSuffix(name, ctx->suffixes_white_list_);

      if (ctx->suffix_ix != -1)
      {
        ctx->fname = name;

        //      trace("file: %s/%s\n", ctx->dir_path, name);

        return;
      }
    }

    if (ndir->dir_entry_prev_interesting_ix < 0)
    {
      //todo code coverage

      Navigator_ResetDir(ctx);
      return;
    }
  }
}

void Navigator_PrevFile(NavigatorContext_Typedef *ctx)
{
  FILINFO *file_info = &(ctx->file_info_);
  NavigatorDir_Typedef *ndir;

  char *name = 0;

  ctx->fname = 0;

  while (1)
  {
    next:

    ndir = &ctx->dir_[ctx->dir_nesting_];

    file_info->fattrib = 0;

    if (ndir->dir_entry_ix_new == -1)
    {
      /* CdUp if we are at the beginning of the current dir */

      if (ctx->dir_nesting_ == 0)
        return; /* we are at the end */

      int start_from = ctx->dir_nesting_;

      for (int ix = start_from; ix >= 0; ix--)
      {
        if (ctx->dir_[ix].dir_entry_ix_new > 0)
        {
          for (int i = start_from; i > ix; i--)
          {
            Navigator_CdUp(ctx);
          }

          goto next;
        }
      }

      return; /* we are at the end */
    }

    Navigator_PrevFileCurrentDir(ctx);

    if (!Navigator_IsOnline())
      return;

    if (ctx->fname)
      return;

    if (file_info->fattrib & AM_DIR)
    {
      if (!CdDown(ctx))
      {
        /* fixme check max nesting */

        if (!Navigator_IsOnline())
          return;

        continue;
      }

      DirPosLastPlusOne(ctx);

      continue;
    }
  }
}

void Navigator_LastFileCurrentDir(NavigatorContext_Typedef *ctx)
{
  DirPosLastPlusOne(ctx);
  Navigator_PrevFileCurrentDir(ctx);
}
