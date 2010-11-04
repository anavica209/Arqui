#include "../../include/syscalls.h"

/***

Este archivo contiene el código de las llamadas del usuario a read()
y a write(), así como las funciones que se encargan de manejar estas
syscalls, del lado del cliente. Tal vez convenga separarlas para que
el usuario no pueda llamar directamente a __write o a __read, que son
las que realmente hacen el trabajo desde el lado del kernel (y en 
teoría, tienen permisos de kernel por lo que no pueden ser utilizadas
por él)

***/

static int writeAux(int fd, const void* buffer, size_t count);
static int readAux(int fd, const void* buffer, size_t count);

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t __write(int fd, const void* buffer, size_t count){
  int i=0;
  switch(fd){
    case STDIN:
    case STDOUT:
        i = writeAux(fd, buffer, count);
	break;
    default:
        break;
  }
  return i;
}


/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, void* buffer, size_t count){
  int i=-1;
  switch(fd){
    case STDIN:
    case STDOUT:
        i=readAux(fd, buffer, count);
        break;

    default:
        break;
  }
  return i;
}


static char * inicialize(char * aux){
  int j;
  for(j=0 ; j<MAXCOL ; j++)
    aux[j]=' ';
}

static void copy(char * d, char * f){
  int i;
  for(i=0; i<MAXCOL ; i++)
    d[i]=f[i];
} 

static void scroll(char m[][MAXCOL], int desde, int hasta){
  char aux[MAXCOL];
  int i;
  inicialize(aux);
  for(i=desde ; i<=hasta ; i++){
    if(i!=0 && i!=hasta)
      copy(m[i-1], m[i]);
    else if(i==0)
      copy(aux, m[0]);
    else
      copy(m[i],inicialize(aux));
  }
}

static int writeAux(int fd, const void* buffer, size_t count){
  int i=0;
  while(((char*)buffer)[i]!=INVALID || i<MAX_BUFFER){
	_write_character(&fd, &(((char *)buffer)[i]), &count);
	i++;
  }
  return i;
}

static int readAux(int fd, const void* buffer, size_t count){
  int i=0;
  while(((char*)buffer)[i]!=INVALID || i<MAX_BUFFER){
	_read_character(&fd, &(((char *)buffer)[i]), &count);
	i++;
  }
  return i;
}
