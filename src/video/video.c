#include "../../include/video.h"
#include "../../include/console.h"
#include "../../include/defs.h"

#define NUMBER_OF_CONSOLES 2

static Console console_array[NUMBER_OF_CONSOLES];

int init_video(){
    int i;
    for (i = 0; i < NUMBER_OF_CONSOLES; i++){
        init_console(console_array + i);
    }
    return 0;
}

int set_terminal(int which){
    if (which >= 0 && which < NUMBER_OF_CONSOLES){
        current_console = console_array + which;
        refresh_video();
    }
    return 0;
}

int refresh_video(){
    // STUB
    // Esto tiene que ser una syscall
    char* video = (char*)VIDEO_ADDRESS;
    int i;
    for (i = 0; i < sizeof(current_console->screen); i++){
        *(video + i) = current_console->screen[i];
    }
    return 0;
}

int update_video(int pointer, size_t length){
    // STUB
    // Esto tiene que ser una syscall
    char* video = (char*)VIDEO_ADDRESS + pointer;
    int i;
    for (i = 0; i < length*2; i++){
        *(video + i) = current_console->screen[i];
    }
}

