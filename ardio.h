#ifndef _ARDIO_H
#define _ARDIO_H

 #ifdef __cplusplus
 #define EXTERNC extern "C"
 #else
 #define EXTERNC
 #endif



#include <stdio.h>


#define files 10

EXTERNC  FILE * fileopen(const char *__restrict_name, const char *__restrict_type);
EXTERNC int fileclose(FILE *f);
EXTERNC size_t fileread(void *buf, size_t _size, size_t _n, FILE *f);
EXTERNC size_t filewrite(const void *buf, size_t _size, size_t _n, FILE *f);

#undef EXTERNC
#endif /* _ARDIO_H */
