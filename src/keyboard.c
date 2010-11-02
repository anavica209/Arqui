#include "../include/libc.h"
#include "../include/keyboard.h"

char _LAST_PRESSED = 0;
int _TICKED = 0;
int _SHIFT = 0;
int  _LANGUAGE = 0;

static char* tempArray = "__1234567890-=__qwertyuiop[]__asdfghjkl;'`_\\zxcvbnm,./____________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________";

static char decode(char keycode, char escaped)
{
    return tempArray[(int)keycode];    
}

void _keyboard_interpreter(int data)
{
    char keycode = data & 0xFF;
    char escape  = (data & 0xFF00) >> 8;

    if (keycode & 0x80) { // Key make
        char translation = decode(keycode^0x80, escape);
        write(0, &translation, 1);
        _LAST_PRESSED = translation;
        _TICKED = false;
    } else { // key release
        _LAST_PRESSED = 0;
    }
}

void _keyboard_repeater()
{
    if (_LAST_PRESSED != 0){
        if (_TICKED){
            write(0, &_LAST_PRESSED, 1);
        } else {
            _TICKED = true;
        }
    }
}


