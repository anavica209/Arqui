#ifndef __keyboard_h__
#define __keyboard_h__

#define KEYBOARD_QUEUE_FD 3

// 
// Esta cola de eventos de teclado tiene su propio file descriptor. Cuando
// el usuario ingresa una tecla, ese evento es guardado en esta cola de
// eventos de teclado, y puede ser leído mediane un
//
// read(KEYBOARD_QUEUE_FD, ...);
//
int keyboard_queue[1024];

//
// Límites de la cola de teclado.
//
int keyboard_queue_begin, keyboard_queue_end;

//
// Función para inicializar el estado de la cola
// 
int keyboard_queue_initialize();

#endif
