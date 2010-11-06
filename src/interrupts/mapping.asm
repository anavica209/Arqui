EXTERN interrupt_80_handler, interrupt_stub_handler

%macro ISR_NOERRCODE 1  ; define una macro que toma un parámetro con
GLOBAL _int_hand_%1     ; la posición en la IDT
  _int_hand_%1:
    cli
    push byte 0
    push byte %1
    jmp _caller%1
%endmacro

%macro ISR_ERRCODE 1    ; Idem anterior, pero sin agregar un error code cero
GLOBAL _int_hand_%1
  _int_hand_%1:
    cli
    push byte %1
    jmp _caller%1
%endmacro

%macro ISR_CALLER 2
  _caller_%1:
    pushad      ; Mete registros en la cola

    mov ax, ds  ; guarda el DS en 16 bits de eax

    push eax
    mov ax, 0x10 ; acá está el kernel code y data segment
    mov ds, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax

    call %2

    pop eax
    mov ds, ax
    mov ex, ax
    mov fs, ax
    mov gs, ax

    popad
    add esp, 8  ; Esto es para el numero de la interrupcion y el error code

    sti
    iret
%endmacro

; Syscalls
ISR_NOERRCODE 80
CALLER 80 interrupt_80_handler


; CPU exceptions
ISR_NOERRCODE 0
CALLER 0, interrupt_stub_handler
ISR_NOERRCODE 1
CALLER 1, interrupt_stub_handler
ISR_NOERRCODE 2
CALLER 2, interrupt_stub_handler
ISR_NOERRCODE 3
CALLER 3, interrupt_stub_handler
ISR_NOERRCODE 4
CALLER 4, interrupt_stub_handler
ISR_NOERRCODE 5
CALLER 5, interrupt_stub_handler
ISR_NOERRCODE 6
CALLER 6, interrupt_stub_handler
ISR_NOERRCODE 7
CALLER 7, interrupt_stub_handler
ISR_ERRCODE 8
CALLER 8, interrupt_stub_handler
ISR_NOERRCODE 9
CALLER 9, interrupt_stub_handler
ISR_ERRCODE 10
CALLER 10, interrupt_stub_handler
ISR_ERRCODE 11
CALLER 11, interrupt_stub_handler
ISR_ERRCODE 12
CALLER 12, interrupt_stub_handler
ISR_ERRCODE 13
CALLER 13, interrupt_stub_handler
ISR_ERRCODE 14
CALLER 14, interrupt_stub_handler
ISR_NOERRCODE 15
CALLER 15, interrupt_stub_handler
ISR_NOERRCODE 16
CALLER 16, interrupt_stub_handler
ISR_NOERRCODE 17
CALLER 17, interrupt_stub_handler
ISR_NOERRCODE 18
CALLER 18, interrupt_stub_handler
ISR_NOERRCODE 19
CALLER 19, interrupt_stub_handler
ISR_NOERRCODE 20
CALLER 20, interrupt_stub_handler
ISR_NOERRCODE 21
CALLER 21, interrupt_stub_handler
ISR_NOERRCODE 22
CALLER 22, interrupt_stub_handler
ISR_NOERRCODE 23
CALLER 23, interrupt_stub_handler
ISR_NOERRCODE 24
CALLER 24, interrupt_stub_handler
ISR_NOERRCODE 25
CALLER 25, interrupt_stub_handler
ISR_NOERRCODE 26
CALLER 26, interrupt_stub_handler
ISR_NOERRCODE 27
CALLER 27, interrupt_stub_handler
ISR_NOERRCODE 28
CALLER 28, interrupt_stub_handler
ISR_NOERRCODE 29
CALLER 29, interrupt_stub_handler
ISR_NOERRCODE 30
CALLER 30, interrupt_stub_handler
ISR_NOERRCODE 31
CALLER 31, interrupt_stub_handler


