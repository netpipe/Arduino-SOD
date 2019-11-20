#ifndef _ARDIO_H
#define _ARDIO_H

//interface file for connecting sd.cpp library into sod.c 

#include <stdio.h>
#define MAX_PATH 1024
#define files 10
#undef fopen
#undef fread
#undef fwrite
#undef fclose
#undef feof
#undef ferror
 #ifdef __cplusplus
 #define EXC extern "C"
 #else
 #define EXC
 #endif



EXC FILE * fopen(const char *__restrict_name, const char *__restrict_type);
EXC int    fclose(FILE *f);
EXC int    feof(FILE *f);
EXC int    ferror(FILE *f);
EXC size_t fread(void *buf, size_t _size, size_t _n, FILE *f);

EXC size_t fwrite(const void *buf, size_t _size, size_t _n, FILE *f);


EXC  int    _chdir(const char *ch);   /* int (*xChdir)(const char *) */
EXC  int    _getcwd(const char *ch);   /* int (*xGetcwd)(SyBlob *) */
EXC  int    _mkdir(const char *ch);    /* int (*xMkdir)(const char *, int, int) */
EXC  int    _rmdir(const char *ch);    /* int (*xRmdir)(const char *) */
EXC  int    _isdir(const char *ch);    /* int (*xIsdir)(const char *) */
EXC  int    _Rename(const char *ch);   /* int (*xRename)(const char *, const char *) */
EXC  int    _Realpath(const char *ch); /*int (*xRealpath)(const char *, SyBlob *)*/
   /* Directory */
EXC  int    _Dir_Open(const char *ch);
EXC  int    _Dir_Close(const char *ch);
EXC  int    _Dir_Read(const char *ch);
EXC  int    _Dir_Rewind(const char *ch);
  /* Systems function */
EXC  int    _unlink(const char *ch); /* int (*xUnlink)(const char *) */
EXC  int    _FileExists(const char *ch); /* int (*xFileExists)(const char *) */
EXC  int64_t    _DiskFreeSpace(const char *ch); /* int64_t (*xFreeSpace)(const char *) */
EXC  int64_t    _DiskTotalSpace(const char *ch); /* int64_t (*xTotalSpace)(const char *) */
EXC  int64_t    _FileSize(const char *ch); /* int64_t (*xFileSize)(const char *) */
EXC  int    _isfile(const char *ch);     /* int (*xIsfile)(const char *) */
EXC  int    _isReadable(const char *ch);    /* int (*xReadable)(const char *) */
EXC  int    _iswritable(const char *ch); /* int (*xWritable)(const char *) */
EXC  int    _isexecutable(const char *ch); /* int (*xExecutable)(const char *) */
EXC  int    _Mmap(const char *ch,void **p,size_t *nb);       /* int (*xMmap)(const char *, void **, size_t *) */
EXC  int    _Unmap(void *p,size_t sz);      /* void (*xUnmap)(void *, size_t);  */
EXC  float  _GetTicks(void);
#endif /* _ARDIO_H */
