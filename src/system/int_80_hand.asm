GLOBAL _int_80_hand
EXTERN __write
EXTERN __read
EXTERN __refresh_video
EXTERN __update_video

_int_80_hand:
  ; Set stack frame
  push ebp
  mov ebp, esp
  ; Do not hear interruptions
  ; TODO

  _check_write:
    cmp ax, 0
    je _call_write

  _check_read:
    cmp ax, 1
    je _call_read

  _check_refresh:
    cmp ax, 2
    je _call_refresh
 
  _check_update:
    cmp ax, 3
    je _call_update

  jmp _exit

  _call_write:
    push edx
    push ecx
    push ebx
    call __write
    addl esp, 0x0Ch ; pop registers, not used
    jmp _exit

  _call_read:
    push edx
    push ecx
    push ebx
    call __read
    addl esp, 0x0Ch ; pop registers, not used
    jmp _exit

  _call_refresh:
    call __refresh_video
    jmp _exit

  _call_update:
    call __update_video
    jmp _exit

  _exit:
    ; Restore stack frame
    pop ebp
    ; Restore interrupts
    ; TODO
    iret 

