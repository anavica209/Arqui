GLOBAL read
GLOBAL write

write:
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

    ret

read:
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

    ret
