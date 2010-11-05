#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/stdio.h"
#include "../include/video.h"
#include "../include/keyboard.h"

DESCR_INT idt[0x100]; // The maximum size of the IDT is 255 entries
IDTR idtr;

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

static void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

/**********************************************
kmain() 
Punto de entrada de código C.
*************************************************/

kmain() 
{

        int i,num;

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        for (i = 0; i <= 0xFF; i++){
            setup_IDT_entry (&idt[i], i, (dword)&_int_stupid_handler, ACS_INT, 0);
        }
        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x09], 0x09, (dword)&_int_09_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x80], 0x80, (dword)&_int_80_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base += (dword)&idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

/* Habilitar interrupciones */

	_Cli();

        _mascaraPIC1(0xFC); 
        _mascaraPIC2(0xFF);
        
	_Sti();

/* Inicializa */

        init_video();
        //init_stdio();
        //keyboard_queue_initialize();
	
        set_language(ENGLISH);
        set_terminal(0);

        //loop();
        while(1);
}

