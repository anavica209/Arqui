#ifndef __console_h__
#define __console_h__

#define COLOR_WHITE_OVER_WHITE 0x77
#define COLOR_WHITE_OVER_BLACK 0x07

typedef struct {
    char screen[80*25*2];

    char pointer_row;
    char pointer_col;

    char input_buffer[80*23];
} Console;

int init_console();

int loop();

#endif
