#include "../../include/video.h"
#include "../../include/console.h"
#include "../../include/defs.h"

#define NUMBER_OF_CONSOLES 2

static Console console_array[NUMBER_OF_CONSOLES];
static int current;

int init_video(){
    int i;
    for (i = 0; i < NUMBER_OF_CONSOLES; i++){
        init_console(console_array+i);
    }
    current = -1;
    return 0;
}

int set_terminal(int which){
    if (which >= 0 && which < NUMBER_OF_CONSOLES){
        current = which;
        refresh_video();
    }
}

int refresh_video(){
    // STUB
    // Esto tiene que ser una syscall
    char* video = CONSOLE_ADDRESS;
    Console* current_console = console_array+current;
    for (int i = 0; i < sizeof(current_console->screen); i++){
        *(video+i) = current_console->screen[i];
    }
    return 0;
}

int update_video(int row, int col, size_t length){
    // STUB
    // Esto tiene que ser una syscall
    char* video = CONSOLE_ADDRESS + (row*80 + col)*2;
    for (int i = 0; i < length*2; i++){
        *(video + i) = current_console->screen[i];
    }
}

