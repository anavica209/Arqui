#include "defs.h"

#ifndef __syscalls_h__
#define __syscalls_h__


/**
    List the calls the user can make
**/
#define WRITE_SYSCALL_ID 0
#define READ_SYSCALL_ID 1
#define OPEN_SYSCALL_ID 2

// I'm still doubting about these two, not sure
#define UPDATE_SCREEN_SYSCALL_ID 4
#define REFRESH_SCREEN_SYSCALL_ID 5

// Poor man's files
#define FILE_ARRAY_SIZE 15

typedef struct{
    int (*write)(const void*, size_t);
    int (*read)(void*, size_t);
} file_descriptor;

file_descriptor FILES[FILE_ARRAY_SIZE];
int FILE_COUNT;

/* open
*
* Recibe como parametros:
*
* - una función a la que llamar cuando se hace write
* - una función para el read
*
* Devuelve:
* Un entero, que es el file descriptor asignado al archivo
**/
int open(int (*write_function)(const void*, size_t), int (*read_function)(void*, size_t));

/* write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t write(int fileDescriptor, const void* buffer, size_t count);

/* read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t read(int fileDescriptor, void* buffer, size_t count);

#endif

