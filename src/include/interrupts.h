#ifndef __interrupts_h__
#define __interrupts_h__

#include "kasm.h"
#include "defs.h"

typedef struct registers
{
   int eds;
   int edi, esi, ebp, esp, ebx, edx, ecx, eax;
   int int_no, err_code;
   int eip, cs, eflags, useresp, ss;
} register_t;

void init_interrupts();
void _remap_pic();

void interrupt_80_handler(register_t registers);

void interrupt_stub_handler(register_t registers);
void interrupt_stuberror_handler(register_t registers);
void irq_handler(register_t registers);

DESCR_INT idt[0x100]; // The maximum size of the IDT is 255 entries
IDTR idtr;
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access);

extern void _int_hand_0();
extern void _int_hand_1();
extern void _int_hand_2();
extern void _int_hand_3();
extern void _int_hand_4();
extern void _int_hand_5();
extern void _int_hand_6();
extern void _int_hand_7();
extern void _int_hand_8();
extern void _int_hand_9();
extern void _int_hand_11();
extern void _int_hand_12();
extern void _int_hand_13();
extern void _int_hand_14();
extern void _int_hand_15();
extern void _int_hand_16();
extern void _int_hand_17();
extern void _int_hand_18();
extern void _int_hand_19();
extern void _int_hand_20();
extern void _int_hand_21();
extern void _int_hand_22();
extern void _int_hand_23();
extern void _int_hand_24();
extern void _int_hand_25();
extern void _int_hand_26();
extern void _int_hand_27();
extern void _int_hand_28();
extern void _int_hand_29();
extern void _int_hand_30();
extern void _int_hand_31();

extern void _irq_0();
extern void _irq_1();
extern void _irq_2();
extern void _irq_3();
extern void _irq_4();
extern void _irq_5();
extern void _irq_6();
extern void _irq_7();
extern void _irq_8();
extern void _irq_9();
extern void _irq_10();
extern void _irq_11();
extern void _irq_12();
extern void _irq_13();
extern void _irq_14();
extern void _irq_15();

#endif
