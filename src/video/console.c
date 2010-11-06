#include "../include/console.h"
#include "../include/video.h"
#include "../include/syscalls.h"
#include "../include/keyboard.h"
#include "../include/defs.h"

int init_console(Console* console){
    int i;

    for (i = 0; i < sizeof(console->screen); i++){
        // Si es par, es el atributo, sino, es el char
        console->screen[i] = i&1 ? COLOR_WHITE_OVER_BLACK : ' ';
    }

    // Draw the bar
    for (i = 1; i < 160; i+=2){
        console->screen[(80*23)*2 + i] = COLOR_WHITE_OVER_WHITE;
    }

    // Draw prompt 
    console->screen[0] = '$';

    console->pointer = 2;
    console->end_buffer = 0;

    for (i = 0; i < sizeof(console->input_buffer); i++){
        console->input_buffer[i] = '\0';
    }
}

int loop(){
    int key_event;
    int retval;
    char new_char;
    while(true){
        retval = read(KEYBOARD_QUEUE_FD, &key_event, 1);
        if (retval){
            if ((new_char = ascii_interpreter(key_event)) != -1){
                console_write_char(new_char);
            } else {
                // TODO: cambiar de consola, etc...
                // Handlear enter,
                // Handlear backspace, etc..
            }
        }
    }
}

int console_write_char(char new_char){
    current_console->input_buffer[current_console->end_buffer++] = new_char;

    current_console->screen[current_console->pointer] = new_char;

    update_video(current_console->pointer, 1);

    current_console->pointer += 2;
}

