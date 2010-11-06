GLOBAL interrupt_09_handler
EXTERN _keyboard_interpreter

interrupt_09_handler:
    push    ds
    push    es
    pushad

    xor     eax,eax

  read:
    in      al, 60h     ; Read from PIC

    cmp     al, 0e0h    ; If it is a extended scan
    jne     nextcheck

    rol    ax, 8
    jmp     read
    
  nextcheck:
    cmp     al, 0e1h    ; Extended scan
    jne     callCfunction

    rol    ax, 8
    jmp     read

  callCfunction:
    push    eax
    call    _keyboard_interpreter
    pop     eax

    mov     al, 20h
    out     20h, al     ; acknowledge to PIC

    ; Restore registers
    popad 
    pop     es
    pop     ds
    iret


	
	
