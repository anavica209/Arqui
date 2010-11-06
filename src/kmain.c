#include "include/defs.h"
#include "include/stdio.h"
#include "include/video.h"
#include "include/keyboard.h"
#include "include/interrupts.h"

kmain() 
{
/* Inicializa */

    init_interrupts();
    init_video();
    init_stdio();

    keyboard_queue_initialize();
    
    set_language(ENGLISH);
    set_terminal(0);

    loop();
}

