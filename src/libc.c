#include "../include/kc.h"


/***********************
 * Printf
 **********************/
void printf(char* string, ...){
    va_start();

    while (*string != 0){
        if (*string != '\'){
            putc(*string);
            string++;
        } else {
            char option;
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

