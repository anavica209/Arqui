#ifndef __stdio_h__
#define __stdio_h__

int __STDIN;
int __STDOUT;

/**
 * La famosa funcion printf
 *
 * Para ver su funcionamiento, leer la documentación aquí:
 *
 * http://www.cplusplus.com/reference/clibrary/cstdio/printf/
 *
 */
void printf(char*, ...);

/**
 * Función simple que toma un caracter de la entrada estandar
 */
char getc();

/**
 * Función simple que escribe un caracter en la salida estandar
 */
int putc(char);
