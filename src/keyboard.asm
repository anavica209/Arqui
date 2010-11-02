GLOBAL _int_09_hand
EXTERN _keyboard_interpreter

_int_09_hand:
    push    ebp
    mov     ebp, esp
    push    ax
    xor     ax,ax

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
    push    ax
    call    _keyboard_interpreter
    pop     ax

    mov     al, 20h
    out     20h, al     ; acknowledge to PIC

    ; Restore register AX and stack frame
    pop     ax
    pop     ebp
    ret

