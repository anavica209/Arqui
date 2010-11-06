GLOBAL _remap_pic
EXTERN irq_handler

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
    push ax
    mov al, 0x11
    out 0x20, al
    out 0xA0, al    

    ; Escribe el offset de cada pic
    mov al, 0x20
    out 0x21, al
    mov al, 0x28
    out 0xA1, al

    ; Sigue con la inicialización... (esto es medio magic numbers)
    mov al, 0x04
    out 0x21, al
    mov al, 0x02
    out 0xA1, al

    ;  Termina
    mov al, 0x01
    out 0x21, al
    out 0xA1, al

    ; Dejamos las máscaras desactivadas todas las interrupciones
    mov al, 0xFF
    out 0x21, al
    out 0xA1, al

    pop ax
    
    sti
    ret



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
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

