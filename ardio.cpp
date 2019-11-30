#include <arduino.h>
#include <alloca.h>
#include <stdio.h>

#define SOD_OK           0 /* Everything went well */
#define SOD_ERR          -1
#define SOD_UNSUPPORTED -1 /* Unsupported Pixel format */
#define SOD_OUTOFMEM    -4 /* Out-of-Memory */
#define SOD_ABORT      -5 /* User callback request an operation abort */
#define SOD_IOERR       -6 /* IO error */
#define SOD_LIMIT       -7 /* Limit reached */

#include "ardio.h"
#include <SD.h>

#ifdef AVR
#include "avrclose.h"
//#error "AVR"
#endif //AVR

bool SDInit=false;




typedef struct fSlot
   {
    File f;
    int  f_EOF;
    int  Error;
    bool Empty=true;
    FILE *Fobj;
   } ;

static struct fSlot *Directory;   
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
  if (ft_type=="r"){FilesSlots[i].f=SD.open(name,FILE_WRITE);}
   else { FilesSlots[i].f=SD.open(name,FILE_WRITE);}
  FilesSlots[i].Empty=false;
  FilesSlots[i].f_EOF=0; FilesSlots[i].Error=0;
  return &FilesSlots[i]; 
}

FILE * fopen(const char *name, const char *ft_type)
{ 
  FILE *OUT;
  #ifdef AVR
  OUT=fdevopen(fileputchar,filegetchar);   //this function din't defined in SAMD stdio.h
  #else
  OUT=new FILE;
  #endif //AVR
  fSlot *Slot=SDOpen(name,ft_type);
  Slot->Fobj=OUT;
  #ifdef AVR
  OUT->udata=Slot; 
  #else
  OUT->_data=(_reent*)Slot; 
  #endif //AVR
  return OUT;// OUT;//send fake FILE pointer
}


int fclose(FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  g->Empty=true;
  g->f.close();
  #ifdef AVR
  FileClose(f);
  #else
   delete f;
  #endif //AVR 

}

int feof(FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  return g->f_EOF;
}

int ferror(FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  return g->Error; 
}

size_t fread(void *buf, size_t _size, size_t _n, FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  return (size_t)g->f.read(buf,_size*_n);
  g->f_EOF=(g->f.position()>=g->f.size())?1:0;
}

size_t filewrite(const void *buf, size_t _size, size_t _n, FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  return g->f.write((const uint8_t*)buf,_size*_n);
}

void   clearerr(FILE *f)
{

  #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  g->f_EOF=0;
  g->Error=0;
}

long   ftell(FILE *f)
{
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  return g->f.position();
}
//fseek has diferense with standard 
// if result position past end of file generate error in standard don't.
int    fseek(FILE *f,long offset, int origin)
{ int seekpos;
   #ifdef AVR
  struct fSlot *g=(fSlot*)(f->udata);
  #else
  struct fSlot *g=(fSlot*)(f->_data);
  #endif //AVR
  switch (origin)
  {
    case SEEK_SET: if (offset<0) {return SOD_ERR;}
                   else {return (g->f.seek(offset))?SOD_OK:SOD_ERR;};
                     
    case SEEK_CUR: seekpos=offset+g->f.position();
                   if (seekpos<0) {return SOD_ERR;}
                   else {return (g->f.seek(seekpos))?SOD_OK:SOD_ERR;};
    case SEEK_END: seekpos=offset+g->f.size();
                   if (seekpos<0) {return SOD_ERR;}
                   else {return (g->f.seek(seekpos))?SOD_OK:SOD_ERR;}
                 
  }
   return SOD_ERR; 
  
}

int  _chdir(const char *zPath)   /* int (*xChdir)(const char *) */
{

}

int    _getcwd(SyBlob *pCtx)   /* int (*xGetcwd)(SyBlob *) */
{

}

int    _mkdir(const char *zPath, int mode, int recursive)    /* int (*xMkdir)(const char *, int, int) */
{

}

int    _rmdir(const char *zPath)    /* int (*xRmdir)(const char *) */
{

}

int    _isdir(const char *zPath)    /* int (*xIsdir)(const char *) */
{

}

int    _Rename(const char *ch)   /* int (*xRename)(const char *, const char *) */
{

}

int    _Realpath(const char *ch) /*int (*xRealpath)(const char *, SyBlob *)*/
{

}
   
   /* Directory */
int    _Dir_Open(const char *ch, void **ppHandle)
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
