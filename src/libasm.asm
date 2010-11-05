GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL  _int_stupid_handler

GLOBAL read
GLOBAL write
GLOBAL open

EXTERN  int_08


SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn

_int_08_hand: ; Handler de INT 8 ( Timer tick)
        push ds
        push es ; Se salvan los registros
        pushad ; Carga de DS y ES con el valor del selector

        mov ax, 10h ; a utilizar.
        mov ds, ax
        mov es, ax
        call int_08
        mov al,20h ; Envio de EOI generico al PIC
        out 20h,al
        popad
        pop es
        pop ds
        iret

_int_stupid_handler:
    nop
    nop
    nop
    iret

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

; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn

