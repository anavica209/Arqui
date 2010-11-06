#include "../include/interrupts.c"
#include "../include/syscalls.c"

static (void*)() irq_function[16];

void init_interrupts(){
    _remap_pic();

    #define _temp_int(X)
    for (i = 0; i < 32; i++){
        setup_IDT_entry (&idt[i], i, (dword)&_temp_int(i), ACS_INT);
    }
    #define _temp_irq(X) _irq_X
    for (i = 32; i < 48; i++){
        setup_IDT_entry (&idt[i], i, (dword)&_temp_irq(i), ACS_INT);
        
        irq_function[i-32] = 0;
    }

    irq_function[8] = interrupt_08_handler;
    irq_function[9] = interrupt_09_handler;


    idtr.base = 0;  
    idtr.base += (dword)&idt;
    idtr.limit = sizeof(idt)-1;
    
    _lidt (&idtr);	

    /* Habilitar interrupciones */
    _Cli();
    _mascaraPIC1(0xFC); 
    _mascaraPIC2(0xFF);
    _Sti();

}

void interrupt_stub_handler(registers_t regs){
    return;
}

void interrupt_80_handler(registers_t regs){
    switch (regs.eax){
        case WRITE_SYSCALL_ID:
            return write(regs.ebx, regs.ecx, regs.edx);
            break;
        
        case READ_SYSCALL_ID: 
            return read(regs.ebx, regs.ecx, regs.edx);
            break;

        case OPEN_SYSCALL_ID:
            return open(regs.ebx, regs.ecx);
            break;

        default:
            break;
    }
    return 0;
}

void irq_handler(register_t registers){
    if (registers->int_no >= 40){
        asm volatile ("outb %0, %1" : : "a"(0x20), "Nd"(0xA0));
    }
    asm volatile ("outb %0, %1" : : "a"(0x20), "Nd"(0x20));

    if (irq_function[registers.int_no] != 0)
    {
        irq_function[registers.int_no](registers);
    }
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
****************************************************************/

static void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset,
    byte access)
{
    item->selector = selector;
    item->offset_l = offset & 0xFFFF;
    item->offset_h = offset >> 16;
    item->access = access;
    item->cero = 0;
}

