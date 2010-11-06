#ifndef __stdio_h__
#define __stdio_h__

/**
 *  File Descriptors para STDIN y STDOUT.
 *
 * Al principio estan vacios, se debe llamar a 
 * la funcion init_stdio() para establecer cuál es el 
 * file descriptor de ellos
 */
#define BUFFER_SIZE 1024
int STDIN_FD;
int STDOUT_FD;
void init_stdio();

/**
 * Las famosas funcion printf y scanf
 *
 * Para ver su funcionamiento, leer la documentación aquí:
 *
 * http://www.cplusplus.com/reference/clibrary/cstdio/printf/
 * http://www.cplusplus.com/reference/clibrary/cstdio/scanf/
 *
 */
void printf(char*, ...);
void scanf(char* string, ...);

/**
 * Función simple que toma un caracter de la entrada estandar
 */
char getc();

/**
 * Función simple que escribe un caracter en la salida estandar
 */
int putc(char);


#endif

