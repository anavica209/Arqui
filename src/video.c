#include "../include/video.h"

Video *controller;
Console *current;

int init_video(Video *control){
    controller = control;
    refresh_video();
}

int _set_terminal(Console *console){
    refresh_video();
}

int refresh_video(){
    
}

int update_video(int row, int col, size_t length){
    
}

