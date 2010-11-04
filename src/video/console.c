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

    console->pointer = 3;
    console->end_buffer = 0;

    for (i = 0; i < sizeof(console->input_buffer); i++){
        console->input_buffer[i] = '\0';
    }
}

int loop(){
    char buffer[80*23];
    while(true){
        int i = 0;
        while ((buffer[i] = getc()) != 0);
        for (int j = 0; j < i; j++){
            console_inputchar(buffer[i]);
        }
    }
}

int console_inputchar(char new_char){
    current_console->input_buffer[current_console->end++] = new_char;

    // TODO: handle special cases, like backspace or tab

    current_console->screen[current_console->pointer] = new_char;

    current_console->pointer += 2;

    update_screen(current_console->pointer, 1);
}
