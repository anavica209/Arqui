#include "../include/libc.h"
#include "../include/syscalls.h"


/***********************
 * Printf
 **********************/
void printf(char* string, ...){
    int i=0;

    while (*string != 0){
        if (*string != '\\'){
            // Esta es la parte fácil. Que linda sería la vida...
            // putc(*string);
            string++;
        } else {
            char option;
            // Busco el primer char que es el tipo de cosa que tengo que hacer
            for (i = 0; string[i]!=0 && string[i]<'z' && string[i]>'a'; i++);
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

char getc(){
    char retval;
    read(STDIN, &retval, 1);
    return retval;
}

int putc(char what){
    write(STDOUT, &what, 1);
}

