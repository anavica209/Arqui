#include "../../include/syscalls.h"

/***

Este archivo contiene las funciones __read y __write, que son
llamadas por la interrupción 80h

También contiene una especie de "open", que permite designar
a un valor entero (file descriptor), dos funciones, una encargada
de leer y otra de escribir en el archivo

***/

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t write(int fd, const void* buffer, size_t count){
    return FILES[fd].write(buffer, count);
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
    return FILES[fd].read(buffer, count);
}

/* __open
*
* Recibe como parametros:
*
* - una función a la que llamar cuando se hace write
* - una función para el read
*
* Devuelve:
* Un entero, que es el file descriptor asignado al archivo
**/
int open(int (*write_function)(const void*, size_t), int (*read_function)(void*, size_t)){
    FILES[FILE_COUNT].write = write_function;
    FILES[FILE_COUNT].read = read_function;
    return FILE_COUNT++;
}
