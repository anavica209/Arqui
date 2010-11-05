#include "../../include/stdio.h"
#include "../../include/console.h"
#include "../../include/syscalls.h"


/***********************
 * Printf
 **********************/
void printf(char* string, ...){
    int i=0;

    while (*string != 0){
        if (*string != '%'){
            // Esta es la parte fácil. Que linda sería la vida...
            putc(*string);
            string++;
        } else {
            char option;
            // Busco el primer char que es el tipo de cosa que tengo que hacer
            for (i = 1; string[i]!=0 && string[i]<'z' && string[i]>'a'; i++);
            switch (string[i]) {
                case 's':
                    break;
                case 'd':
                case 'i':
                    break;
                case 'o':
                    break;
                case 'h':
                    break;
                case 'x':
                    break;
                case 'X':
                    break;
                case 'n':
                    break;
                case '%':
                    break;
                case 0:
                    break;
            }
        }
    }
}

/***
 *    Scan formated input
 *
 * this is another famous one
 *
 **/
void scanf(char* string, ...){
    return;
}


/**
 * These two functions are very well known, and basic
 */
char getc(){
    char retval;
    while (read(STDIN_FD, (void*)&retval, 1) != 0);
    return retval;
}

int putc(const char what){
    return write(STDOUT_FD, (const void*)&what, 1);
}


/**
 *
 * Some very private things
 *
 **/

static char _stdin_buffer[BUFFER_SIZE];

static int _begin_stdin;
static int _end_stdin;

static int __read_stdin(void* buffer, size_t length){
    int i;
    char* _buffer = buffer;
    for (i = 0; i < length &&
        (_begin_stdin + i)%BUFFER_SIZE != _end_stdin; i++)
    {
        *(_buffer++) = _stdin_buffer[(_begin_stdin + i)%BUFFER_SIZE];
    }
    _begin_stdin = (_begin_stdin + i)%BUFFER_SIZE;
    return i;
}

static int __write_stdin(const void* buffer, size_t length){
    int i;
    const char* _buffer = (char*)buffer;
    for (i = 0; i < length &&
        (_end_stdin + i)%BUFFER_SIZE != _begin_stdin; i++)
    {
        _stdin_buffer[(_end_stdin + 1)%BUFFER_SIZE] = *(_buffer++);
    }
    return i;
}

/**
 * No sé como sería la lectura del stdout, lo dejo en blanco
 */
static int __read_stdout(void* buffer, size_t length){
    return 0;
}

/**
 * Escribo directamente a la consola actual
 */
static int __write_stdout(const void* buffer, size_t length){
    int i = 0;
    char* _buffer = (char*)buffer;
    for (i = 0; i < length; i++){
        console_write_char(*(_buffer++));
    };
}


/**
 *  Back to public stuff. This function sets up the STDIN and STDOUT
 *
 */
void init_stdio(){
    STDIN_FD = open(__write_stdin, __read_stdin);
    STDOUT_FD = open(__write_stdout, __read_stdout);
    _begin_stdin = 0;
    _end_stdin = 0;
}

