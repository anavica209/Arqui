#include "../../include/defs.h"
#include "../../include/keyboard.h"

static int _LAST_PRESSED = 0;
static int _TICKED = 0;
static int _SHIFT = 0;
static char _SPACE = ' ';

static char* english    = "__1234567890-=__qwertyuiop[]__asdfghjkl;'`_\\zxcvbnm,./____________________";
static char* englishmays= "__!@#$%^&*()_+__QWERTYUIOP{}__ASDFGHJKL:_~_|ZXCVBNM<>?_____________________";
static char* spanish	= "__1234567890'¡_qwertyuiop`+__asdfghjklñ<zxcvbnm,.-_________________________";
static char* spanishmays= "__!__$%&/()=?¿__QWERTYUIOP^*_ASDFGHJKLÑ¨Ç_>ZXCVBNM;:_______________________";

static int shift = false;

/**
 *
 *  Este es el intérprete de keycodes que deberían usar varias
 * aplicaciones del SO, sobre todo la terminal, y el kernel cuando 
 * escriba en el STDIN el valor de las cosas del teclado.
 *
 */
char ascii_interpreter(int keycode)
{
    char escaped = (keycode>>8) & 0xFF;
    keycode &= 0xFF;
	
    char caracter=0;

    if((escaped== 0x2A) || (escaped == 0x36)){
        shift = true;
    }
	
    if(keycode==0x39){

        //space bar
        return _SPACE;

    } else if (keycode==0x0f) {
    
        //tab key changes keyboard language (for now)
        set_language(!CURRENT_LANGUAGE);

    } else if (keycode < 96){
        if (CURRENT_LANGUAGE==ENGLISH) {
            // We're talking in englishh
            if(!shift){
                caracter= english[keycode];    
            } else {
                caracter= englishmays[keycode];
            }
        } else {
            // Hablamos español, orale chamaco!
            if(!shift){
                caracter= spanish[keycode];
            } else {
                caracter= spanishmays[keycode];
            }
        }
    }
    return caracter ? caracter : -1;
}

//
// Bastante descriptivo lo que hace esta funcion...
//
void set_language(int lang){
    CURRENT_LANGUAGE = lang;
}

//
// Inicializa la cola del teclado
//
int keyboard_queue_initialize(){
    keyboard_queue_begin = 0;
    keyboard_queue_end = 0;
}

// Función llamda cuando alguien hace un write en KEYBOARD_QUEUE_FD
int keyboard_queue_write(int keycode){
    int next = keyboard_queue_end + 1;
    if (next == KEYBOARD_QUEUE_SIZE){
        next = 0;
    }
    if (next != keyboard_queue_begin){
        keyboard_queue[keyboard_queue_end] = keycode;
        keyboard_queue_end = next;
        return 1;
    } else {
        // Could not write. Buffer full
        return -1;
    }
}

// Función llamada cuando alguien hace un read a KEYBOARD_QUEUE_FD
int keyboard_queue_read(){
    if (keyboard_queue_begin != keyboard_queue_end){

        // Me guardo el valor del primer elemento de la cola
        int retval = keyboard_queue[keyboard_queue_begin];

        // Incremento el valor de donde empieza mi cola y "doy la vuelta"
        // si es necesario (me pasé del final del arreglo)
        keyboard_queue_begin++;
        if (keyboard_queue_begin == KEYBOARD_QUEUE_SIZE){
            keyboard_queue_begin = 0;
        }
        return retval; 
    } else {
        // No hay nada para leer aquí muchachos...
        return -1;
    }
}

/**
 *
 *
 *
 *   Estas funciones son usadas por las interrupuciones de
 *   teclado
 *
 *
 */
void _keyboard_interpreter(int data)
{
    // KEYBOARD_QUEUE_FD está declarado en keyboard.h
    // y es un file descriptor para la cola de eventos de teclado
    write(KEYBOARD_QUEUE_FD, data, 1);

    if (data & 0x80) { // Key make
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


