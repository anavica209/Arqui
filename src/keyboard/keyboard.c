#include "../../include/defs.h"
#include "../../include/keyboard.h"

static int _LAST_PRESSED = 0;
static int _TICKED = 0;
static int _SHIFT = 0;
static int  _LANGUAGE = 0;

static char* tempArray = "__1234567890-=__qwertyuiop[]__asdfghjkl;'`_\\zxcvbnm,./____________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________";

void _keyboard_interpreter(int data)
{
    // KEYBOARD_QUEUE_FD está declarado en keyboard.h
    // y es un file descriptor para la cola de eventos de teclado
    write(KEYBOARD_QUEUE_FD, data, 1);

    if (keycode & 0x80) { // Key make
        _LAST_PRESSED = data;
        _TICKED = false;
    } else { // key release
        _LAST_PRESSED = 0;
    }
}

void _keyboard_repeater()
{
    if (_LAST_PRESSED != 0){
        if (_TICKED){
            write(KEYBOARD_QUEUE_FD, &_LAST_PRESSED, 1);
        } else {
            _TICKED = true;
        }
    }
}


