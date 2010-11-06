#include "../include/interrupts.h"
#include "../include/syscalls.h"

static int irq_function[16];

void init_interrupts(){
    int i;
    _remap_pic();

    setup_IDT_entry (&idt[0], 0, (dword)&_int_hand_0, ACS_INT);
    setup_IDT_entry (&idt[1], 1, (dword)&_int_hand_1, ACS_INT);
    setup_IDT_entry (&idt[2], 2, (dword)&_int_hand_2, ACS_INT);
    setup_IDT_entry (&idt[3], 3, (dword)&_int_hand_3, ACS_INT);
    setup_IDT_entry (&idt[4], 4, (dword)&_int_hand_4, ACS_INT);
    setup_IDT_entry (&idt[5], 5, (dword)&_int_hand_5, ACS_INT);
    setup_IDT_entry (&idt[6], 6, (dword)&_int_hand_6, ACS_INT);
    setup_IDT_entry (&idt[7], 7, (dword)&_int_hand_7, ACS_INT);
    setup_IDT_entry (&idt[8], 8, (dword)&_int_hand_8, ACS_INT);
    setup_IDT_entry (&idt[9], 9, (dword)&_int_hand_9, ACS_INT);
    setup_IDT_entry (&idt[10], 10, (dword)&_int_hand_10, ACS_INT);
    setup_IDT_entry (&idt[11], 11, (dword)&_int_hand_11, ACS_INT);
    setup_IDT_entry (&idt[12], 12, (dword)&_int_hand_12, ACS_INT);
    setup_IDT_entry (&idt[13], 13, (dword)&_int_hand_13, ACS_INT);
    setup_IDT_entry (&idt[14], 14, (dword)&_int_hand_14, ACS_INT);
    setup_IDT_entry (&idt[15], 15, (dword)&_int_hand_15, ACS_INT);
    setup_IDT_entry (&idt[16], 16, (dword)&_int_hand_16, ACS_INT);
    setup_IDT_entry (&idt[17], 17, (dword)&_int_hand_17, ACS_INT);
    setup_IDT_entry (&idt[18], 18, (dword)&_int_hand_18, ACS_INT);
    setup_IDT_entry (&idt[19], 19, (dword)&_int_hand_19, ACS_INT);
    setup_IDT_entry (&idt[20], 20, (dword)&_int_hand_20, ACS_INT);
    setup_IDT_entry (&idt[21], 21, (dword)&_int_hand_21, ACS_INT);
    setup_IDT_entry (&idt[22], 22, (dword)&_int_hand_22, ACS_INT);
    setup_IDT_entry (&idt[23], 23, (dword)&_int_hand_23, ACS_INT);
    setup_IDT_entry (&idt[24], 24, (dword)&_int_hand_24, ACS_INT);
    setup_IDT_entry (&idt[25], 25, (dword)&_int_hand_25, ACS_INT);
    setup_IDT_entry (&idt[26], 26, (dword)&_int_hand_26, ACS_INT);
    setup_IDT_entry (&idt[27], 27, (dword)&_int_hand_27, ACS_INT);
    setup_IDT_entry (&idt[28], 28, (dword)&_int_hand_28, ACS_INT);
    setup_IDT_entry (&idt[29], 29, (dword)&_int_hand_29, ACS_INT);
    setup_IDT_entry (&idt[30], 30, (dword)&_int_hand_30, ACS_INT);
    setup_IDT_entry (&idt[31], 31, (dword)&_int_hand_31, ACS_INT);

    setup_IDT_entry (&idt[32], 32, (dword)&_irq_0, ACS_INT);
    irq_function[0] = 0;
    setup_IDT_entry (&idt[33], 33, (dword)&_irq_1, ACS_INT);
    irq_function[1] = 0;
    setup_IDT_entry (&idt[34], 34, (dword)&_irq_2, ACS_INT);
    irq_function[2] = 0;
    setup_IDT_entry (&idt[35], 35, (dword)&_irq_3, ACS_INT);
    irq_function[3] = 0;
    setup_IDT_entry (&idt[36], 36, (dword)&_irq_4, ACS_INT);
    irq_function[4] = 0;
    setup_IDT_entry (&idt[37], 37, (dword)&_irq_5, ACS_INT);
    irq_function[5] = 0;
    setup_IDT_entry (&idt[38], 38, (dword)&_irq_6, ACS_INT);
    irq_function[6] = 0;
    setup_IDT_entry (&idt[39], 39, (dword)&_irq_7, ACS_INT);
    irq_function[7] = 0;
    setup_IDT_entry (&idt[40], 40, (dword)&_irq_8, ACS_INT);
    irq_function[8] = 0;
    setup_IDT_entry (&idt[41], 41, (dword)&_irq_9, ACS_INT);
    irq_function[9] = 0;
    setup_IDT_entry (&idt[42], 42, (dword)&_irq_10, ACS_INT);
    irq_function[10] = 0;
    setup_IDT_entry (&idt[43], 43, (dword)&_irq_11, ACS_INT);
    irq_function[11] = 0;
    setup_IDT_entry (&idt[44], 44, (dword)&_irq_12, ACS_INT);
    irq_function[12] = 0;
    setup_IDT_entry (&idt[45], 45, (dword)&_irq_13, ACS_INT);
    irq_function[13] = 0;
    setup_IDT_entry (&idt[46], 46, (dword)&_irq_14, ACS_INT);
    irq_function[14] = 0;
    setup_IDT_entry (&idt[47], 47, (dword)&_irq_15, ACS_INT);
    irq_function[15] = 0;


    irq_function[8] = (int)interrupt_08_handler;
    irq_function[9] = (int)interrupt_09_handler;


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

void interrupt_stub_handler(register_t regs){
    return;
}

int interrupt_80_handler(register_t regs){
    switch (regs.eax){
        case WRITE_SYSCALL_ID:
            return write(regs.ebx, (const void*) regs.ecx, regs.edx);
            break;
        
        case READ_SYSCALL_ID: 
            return read(regs.ebx, (void*) regs.ecx, regs.edx);
            break;

        case OPEN_SYSCALL_ID:
            return open((int (*)(const void *, size_t)) regs.ebx,
                (int (*)(void *, size_t)) regs.ecx);
            break;

        default:
            break;
    }
    return 0;
}

void irq_handler(register_t registers){
    if (registers.int_no >= 40){
        asm volatile ("outb %0, %1" : : "a"((char)0x20), "Nd"(0xA0));
    }
    asm volatile ("outb %0, %1" : : "a"((char)0x20), "Nd"(0x20));

    if (irq_function[registers.int_no] != 0)
    {
        ((void(*)(register_t))(irq_function[registers.int_no]))(registers);
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

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access)
{
    item->selector = selector;
    item->offset_l = offset & 0xFFFF;
    item->offset_h = offset >> 16;
    item->access = access;
    item->cero = 0;
}

