#include "../../include/defs.h"
#include "../../include/keyboard.h"

static char _LAST_PRESSED = 0;
static int 	_TICKED = 0;
static int 	_SHIFT 	= 0;
static int  _LANGUAGE = ENGLISH;  //default
static char _SPACE = ' ';

static char* tempArray =  "__1234567890-=__qwertyuiop[]__asdfghjkl;'`_\\zxcvbnm,./____________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________"
    "_________________________________________________________________________________________________";
static char* englishmays= "__!@#$%^&*()_+__QWERTYUIOP{}__ASDFGHJKL:_~_|ZXCVBNM<>?_____________________";
static char* spanish	= "__1234567890'¡_qwertyuiop`+__asdfghjklñ<zxcvbnm,.-____________________";
static char* spanishmays= "__!__$%&/()=?¿__QWERTYUIOP^*_ASDFGHJKLÑ¨Ç_>ZXCVBNM;:_____________________";

static char decode(char keycode, char escaped)
{
	
	int shift = OFF;
	char caracter=0;
	if((escaped== 0x2A) || (escaped == 0x36))
		shift = ON;
	
// tecla para cambiar de consola ?
// que pasa con enter
// que pasa con el delete. necesito retroceder una pos en el buffer y 'sobreescribir' lo que habia.
// quiza se podria hacer pasandole a write un 0 en la cantidad de chars a escribir, ultimo argumento.

	if(keycode==0x39)			//space bar
		return _SPACE;
	else-if(keycode==0x0f){		//tab key to change keyboard language
		changelanguage();
		return NONE;			//no key, do not write in buffer. 
	}
	else-if(_LANGUAGE==ENGLISH){
		if(shift == OFF)
			caracter= tempArray[(int)keycode];    
		else
			caracter= englishmays[(int)keycode];
	}
	else{
		if(shift == OFF)
			caracter= spanish[(int)keycode];
		else
			caracter= spanishmays[(int)keycode];
	}
	return caracter;
	
}

void changelanguage(){
	if(_LANGUAGE == ENGLISH)
		_LANGUAGE = SPANISH;
	else
		_LANGUAGE = ENGLISH;
}

void _keyboard_interpreter(int data)
{
    char keycode = data & 0xFF;
    char escape  = (data & 0xFF00) >> 8;

    if (keycode & 0x80) { // Key make
        char translation = decode(keycode^0x80, escape);
        if(translation != NONE)								//si la tecla apretada no es para escribir
			write(0, &translation, 1);						//no necesito imprimir
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


