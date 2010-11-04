#include "../../include/console.h"
#include "../../include/syscalls.h"

int init_console(Console* console){
    int i;

    for (i = 0; i < sizeof(console->screen); i++){
        // Si es par, es el atributo, sino, es el char
        console->screen[i] = i&1 ? ' ' : COLOR_WHITE_OVER_BLACK;
    }

    // Draw the bar
    for (i = 0; i < 25*2; i+=2){
        console->screen[80*23*2 + i] = COLOR_WHITE_OVER_WHITE;
    }

    // Draw prompt 
    console->screen[1] = '$';

    console->pointer_row = 0;
    console->pointer_col = 1;

    for (i = 0; i < sizeof(console->input_buffer); i++){
        console->input_buffer = 0;
    }
}

int loop(){
}

