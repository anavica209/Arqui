GLOBAL _remap_pic

%macro IRQ 2
GLOBAL _irq_%1
 _irq_%1:
  cli
  push byte 0
  push byte %2
  jmp _irq_common_stub
%endmacro

_remap_pic:
    cli

    ; Empieza el proceso de inicializacion
    outb 0x20, 0x11
    outb 0xA0, 0x11
    
    ; Escribe el offset de cada pic
    outb 0x21, 0x20
    outb 0xA1, 0x28

    ; Sigue con la inicialización... (esto es medio magic numbers)
    outb 0x21, 0x04
    outb 0xA1, 0x02

    ;  Termina
    outb 0x21, 0x01
    outb 0xA1, 0x01

    ; Dejamos las máscaras desactivadas todas las interrupciones
    outb 0x21, 0xFF
    outb 0xA1, 0xFF
    
    sti
    ret


EXTERN irq_handler

_irq_common_stub:
   pushad

   mov ax, ds
   push eax

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx        ; reload the original data segment descriptor
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popad
   add esp, 8
   sti
   iret 

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38

IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

