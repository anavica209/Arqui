/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/

static int writeAux(int fd, const void* buffer, size_t count){
  int i=0;
  while(((char*)buffer)[i]!=INVALID || i<MAX_BUFFER){
	_write_character(&fd, &(((char *)buffer)[i]), &count);
	i++;
  }
  return i;
}


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

static int readAux(int fd, const void* buffer, size_t count){
  int i=0;
  while(((char*)buffer)[i]!=INVALID || i<MAX_BUFFER){
	_read_character(&fd, &(((char *)buffer)[i]), &count);
	i++;
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
  int i=0;
  switch(fd){
    case STDIN:		i=readAux(fd, buffer, count);
			break;
    case STDOUT:	i=readAux(fd, buffer, count);
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

void scroll(char m[][MAXCOL], int desde, int hasta){
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
