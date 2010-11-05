GLOBAL read
GLOBAL write
GLOBAL open

write:
    push ebp
    mov  ebp, esp
    push ebx
    push ecx
    push edx

    mov eax, 0
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    int 80h

    pop edx
    pop ecx
    pop ebx
    pop ebp

    ret

read:
    push ebp
    mov  ebp, esp
    push ebx
    push ecx
    push edx

    mov eax, 1
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    int 80h

    pop edx
    pop ecx
    pop ebx
    pop ebp

    ret

open:
    push ebp
    mov  ebp, esp
    push ebx
    push ecx

    mov eax, 2
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    int 80h

    pop ecx
    pop ebx
    pop ebp

    ret

