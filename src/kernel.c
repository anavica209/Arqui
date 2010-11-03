#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/libc.h"

DESCR_INT idt[0x81];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/

int writeAux(int fd, const void* buffer, size_t count){
  int i=0;
  while(((char*)buffer)[i]!=INVALID || i<MAX_BUFFER){
	_write_character(&fd, &(((char *)buffer)[i]), &count);
	i++;
  }
  return i;
}


size_t write(int fd, const void* buffer, size_t count){
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

int readAux(int fd, const void* buffer, size_t count){
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
size_t read(int fd, void* buffer, size_t count){
  int i=0;
  switch(fd){
    case STDIN:		i=readAux(fd, buffer, count);
			break;
    case STDOUT:	i=readAux(fd, buffer, count);
			break;
  }
  return i;
}



char * inicialize(char * aux){
  int j;
  for(j=0 ; j<MAXCOL ; j++)
    aux[j]=' ';
}

void copy(char * d, char * f){
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




/**********************************************
kmain() 
Punto de entrada de código C.
*************************************************/

kmain() 
{

        int i,num;

/* Borra la pantalla. */ 

	k_clear_screen();


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x09], 0x09, (dword)&_int_09_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x80], 0x80, (dword)&_int_80_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

/* Habilitar interrupciones */

	_Cli();

        _mascaraPIC1(0xFC); 
        _mascaraPIC2(0xFF);
        
	_Sti();

/* Bucle principal */

        while(1)
        {
        }
	
}

