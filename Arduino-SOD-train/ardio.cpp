#include <arduino.h>
#include <alloca.h>
#include <stdio.h>



#include "ardio.h"
#include <SD.h>

bool SDInit=false;




typedef struct fSlot
   {
    File f;
    int  f_EOF;
    int  Error;
    bool Empty=true;
   } ;
static struct fSlot FilesSlots[files];
//this functions defines for fdevopen
static int  fileputchar(char c, FILE *stream)
{
	return 0;
}

static int  filegetchar(FILE *stream)
{
	char data =0; //Temporarly store received data
	return data;
}

fSlot* SDOpen(const char *name, const char *ft_type)
{
   int i=0;
  struct fSlot *g;
  while((!FilesSlots[i].Empty)&&(i<files)) //finding 
  {i++;}
  if (i>=files) {return NULL;}
  
  FilesSlots[i].f=SD.open(name,FILE_WRITE);
  FilesSlots[i].Empty=false;
  FilesSlots[i].f_EOF=0; FilesSlots[i].Error=0;
  return &FilesSlots[i]; 
}

FILE * fopen(const char *name, const char *ft_type)
{
  //FILE *OUT=fdevopen(fileputchar,filegetchar);   //this function din't defined in SAMD stdio.h
  return (FILE*)SDOpen(name,ft_type);// OUT;//send fake FILE pointer
}


int fclose(FILE *f)
{
  struct fSlot *g=(fSlot*)(f);
  g->Empty=true;
  g->f.close();

}

int feof(FILE *f)
{
  struct fSlot *g=(fSlot*)(f);
  return g->f_EOF;
}

int ferror(FILE *f)
{
  struct fSlot *g=(fSlot*)(f);
  return g->Error; 
}

size_t fread(void *buf, size_t _size, size_t _n, FILE *f)
{
  struct fSlot *g=(fSlot*)(f);
  return (size_t)g->f.read(buf,_size*_n);
  g->f_EOF=(g->f.position()>=g->f.size())?1:0;
}

size_t filewrite(const void *buf, size_t _size, size_t _n, FILE *f)
{
  struct fSlot *g=(fSlot*)(f);
  return g->f.write((const uint8_t*)buf,_size*_n);
}

int  _chdir(const char *ch)   /* int (*xChdir)(const char *) */
{

}

int    _getcwd(const char *ch)   /* int (*xGetcwd)(SyBlob *) */
{

}

int    _mkdir(const char *ch)    /* int (*xMkdir)(const char *, int, int) */
{

}

int    _rmdir(const char *ch)    /* int (*xRmdir)(const char *) */
{

}

int    _isdir(const char *ch)    /* int (*xIsdir)(const char *) */
{

}

int    _Rename(const char *ch)   /* int (*xRename)(const char *, const char *) */
{

}

int    _Realpath(const char *ch) /*int (*xRealpath)(const char *, SyBlob *)*/
{

}
   
   /* Directory */
int    _Dir_Open(const char *ch)
{

}

int    _Dir_Close(const char *ch)
{

}

int    _Dir_Read(const char *ch)
{

}

int    _Dir_Rewind(const char *ch)
{

}
  
  /* Systems function */


int    _unlink(const char *ch) /* int (*xUnlink)(const char *) */
{

}

int    _FileExists(const char *ch) /* int (*xFileExists)(const char *) */
{

}

int64_t    _DiskFreeSpace(const char *ch) /* int64_t (*xFreeSpace)(const char *) */
{

}

int64_t    _DiskTotalSpace(const char *ch) /* int64_t (*xTotalSpace)(const char *) */
{

}

int64_t    _FileSize(const char *ch) /* int64_t (*xFileSize)(const char *) */
{

}

int    _isfile(const char *ch)     /* int (*xIsfile)(const char *) */
{

}

int    _isReadable(const char *ch)    /* int (*xReadable)(const char *) */
{

}

int    _iswritable(const char *ch) /* int (*xWritable)(const char *) */
{

}

int    _isexecutable(const char *ch) /* int (*xExecutable)(const char *) */
{

}

int    _Mmap(const char *ch,void **p,size_t *nb)       /* int (*xMmap)(const char *, void **, size_t *) */
{

}

int    _Unmap(void *p,size_t sz)      /* void (*xUnmap)(void *, size_t);  */
{

}

float  _GetTicks(void)
{

}  
