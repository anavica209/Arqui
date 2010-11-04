#ifndef __keyboard_h__
#define __keyboard_h__

// 
// Esta cola de eventos de teclado tiene su propio file descriptor. Cuando
// el usuario ingresa una tecla, ese evento es guardado en esta cola de
// eventos de teclado, y puede ser leído mediane un
//
// read(KEYBOARD_QUEUE_FD, ...);
//
#define KEYBOARD_QUEUE_FD 3
int keyboard_queue[1024];

//
// Límites de la cola de teclado.
//
int keyboard_queue_begin, keyboard_queue_end;

//
// Función para inicializar el estado de la cola
// 
int keyboard_queue_initialize();

//
// Función handler para el read y write al file descriptor
//
int keyboard_queue_write(int keycode);
int keyboard_queue_read();

//
// Handling lenguajes y ascii
//

#define ENGLISH	0		
#define SPANISH 1
#define CURRENT_LANGUAGE 0

//
// Dado un key event, esta función devuelve el char ascii que corresponde 
// de acuerdo al lenguaje actual
//
char ascii_interpreter(int data);

// 
// Change the language to another
//
void set_language(int lang);

#endif

