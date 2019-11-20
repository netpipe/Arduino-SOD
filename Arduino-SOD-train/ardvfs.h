#include "ardio.h"

//this file need for suchesful linking functions into sod


static int  ArdVfs_chdir(const char *ch)   /* int (*xChdir)(const char *) */
{
_chdir(ch);
}

static int    ArdVfs_getcwd(const char *ch)   /* int (*xGetcwd)(SyBlob *) */
{
_getcwd(ch);
}

static int    ArdVfs_mkdir(const char *ch)    /* int (*xMkdir)(const char *, int, int) */
{
_mkdir(ch);
}

static int    ArdVfs_rmdir(const char *ch)    /* int (*xRmdir)(const char *) */
{
_rmdir(ch);
}

static int    ArdVfs_isdir(const char *ch)    /* int (*xIsdir)(const char *) */
{
_isdir(ch);
}

static int    ArdVfs_Rename(const char *ch)   /* int (*xRename)(const char *, const char *) */
{
_Rename(ch);
}

static int    ArdVfs_Realpath(const char *ch) /*int (*xRealpath)(const char *, SyBlob *)*/
{
_Realpath(ch);
}
   
   /* Directory */
static int    ArdDir_Open(const char *ch)
{
_Dir_Open(ch);
}

static int    ArdDir_Close(const char *ch)
{
_Dir_Close(ch);
}

static int    ArdDir_Read(const char *ch)
{
_Dir_Read(ch);
}

static int    ArdDir_Rewind(const char *ch)
{
 _Dir_Rewind(ch);
}
  
  /* Systems function */


static int    ArdVfs_unlink(const char *ch) /* int (*xUnlink)(const char *) */
{
 _unlink(ch);
}

static int    ArdVfs_FileExists(const char *ch) /* int (*xFileExists)(const char *) */
{
 _FileExists(ch);
}

static int64_t    ArdVfs_DiskFreeSpace(const char *ch) /* int64_t (*xFreeSpace)(const char *) */
{
 _DiskFreeSpace(ch);
}

static int64_t    ArdVfs_DiskTotalSpace(const char *ch) /* int64_t (*xTotalSpace)(const char *) */
{
 _DiskTotalSpace(ch);
}

static int64_t    ArdVfs_FileSize(const char *ch) /* int64_t (*xFileSize)(const char *) */
{
_FileSize(ch);
}

static int    ArdVfs_isfile(const char *ch)     /* int (*xIsfile)(const char *) */
{
_isfile(ch);
}

static int    ArdVfs_isReadable(const char *ch)    /* int (*xReadable)(const char *) */
{
_isReadable(ch);
}

static int    ArdVfs_iswritable(const char *ch) /* int (*xWritable)(const char *) */
{
_iswritable(ch);
}

static int    ArdVfs_isexecutable(const char *ch) /* int (*xExecutable)(const char *) */
{
_isexecutable(ch);
}

static int    ArdVfs_Mmap(const char *ch,void **p,size_t *nb)       /* int (*xMmap)(const char *, void **, size_t *) */
{
 _Mmap(ch,p,nb);
}

static int    ArdVfs_Unmap(void *p,size_t sz)      /* void (*xUnmap)(void *, size_t);  */
{
_Unmap(p,sz);
}

static float  ArdVfs_GetTicks(void)
{
_GetTicks();
}  
