#include <arduino.h>
#include <alloca.h>
#include "ardio.h"
#include <SD.h>

bool SDInit=false;

typedef struct fSlot
   {
    File f;
    bool Empty=true;
   } ;
static struct fSlot FilesSlots[files];


FILE * fileopen(const char *__restrict _name, const char *__restrict _type)
{
  int i=0;
  struct fSlot *g;
 
  while((!FilesSlots[i].Empty)&&(i<files))
  {i++;}
  if (i>=files) {return NULL;}
  FilesSlots[i].f=SD.open(__restrict _name);
  FilesSlots[i].Empty=false;
  g=&FilesSlots[i];
  FILE *OUT=(FILE*)g;
  return OUT;
}


int fileclose(FILE *f)
{
  struct fSlot *g=(fSlot*)f;
  g->f.close();
  g->Empty=true;
}
size_t fileread(void *buf, size_t _size, size_t _n, FILE *f)
{
  struct fSlot *g=(fSlot*)f;
  return (size_t)g->f.read(buf,_size*_n);
  ;
}

size_t filewrite(const void *buf, size_t _size, size_t _n, FILE *f)
{
  struct fSlot *g=(fSlot*)f;
  return g->f.write((const uint8_t*)buf,_size*_n);
}
