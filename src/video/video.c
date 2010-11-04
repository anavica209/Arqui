#include "../../include/video.h"
#include "../../include/defs.h"

static Console *current;

static Console console_array[2];

int init_video(){
    
    refresh_video();
    return 0;
}

int set_terminal(Console *console){
    refresh_video();
    return 0;
}

int refresh_video(){
    return 0;
}

int update_video(int row, int col, size_t length){
    return 0;
}

