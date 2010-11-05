#ifndef __console_h__
#define __console_h__

#define COLOR_WHITE_OVER_WHITE 0xFF
#define COLOR_WHITE_OVER_BLACK 0x0F

typedef struct {
    char screen[80*25*2];
    char input_buffer[80*23];
    int end_buffer;
    int pointer;
} Console;

Console* current_console;

int init_console();

int loop();


#endif
