GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL  _write_character
GLOBAL  _read_character

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


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pushad                          ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_08                 
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popad                            
        pop     es
        pop     ds
        iret


; Debug para el BOCHS, detiene la ejecuciÃ³; Para continuar colocar en el BOCHSDBG: set $eax=0
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


_write_character:
;	mov eax,4		Servicio 4: escritura (write). Los parámetros necesarios son:
;//	mov bx,1		   EBX: unidad de salida (1: salida estándar)
;//	mov ecx,oración		   ECX: Puntero a un área de memoria donde se encuentran los caracteres a mostrar.
;//	mov edx,100		   EDX: Número máximo de caracteres a mostrar. 
	push	ebp
	mov	ebp, esp
;	//servicio
	push eax
	mov eax,4
;se pone en la pila el primer elemento fd 
	
	push 	ebx
	mov	ebx,[ss: ebp + 6]	;//dejo en algun registro el valor del file descriptor
;//se agrega a la pila direccion de buffer y se desreferencia como un char
	push 	ecx
        mov     ecx, [ss: ebp + 6] ; ds:bx = puntero a buffer 
	rol	ecx,16		    	
	lidt    [ds: ecx]          ; carga primer char
	
;//valor del count
	push 	edx
	mov	edx,[ss: ebp + 6]	;//dejo en algun registro la cantidad a copiar	
 
	int 80h
	pop	edx
	pop	ecx		;libera la pila
	pop	ebx
	pop     eax
	pop     ebp
	retn


_read_character:
;//mov eax,3	Servicio 3: lectura (read). Los parámetros necesarios son:
;//mov bx,0	    EBX: unidad de entrada (0: entrada estándar).
;//mov ecx,oración	    ECX: Puntero a un área de memoria donde se dejarán los caracteres obtenidos.
;//mov edx,100 	    EDX: Número máximo de caracteres a leer.
	push	ebp
	mov	ebp, esp
;	//servicio
	push eax
	mov eax,3
;se pone en la pila el primer elemento fd 
	
	push 	ebx
	mov	ebx,[ss: ebp + 6]	;//dejo en algun registro el valor del file descriptor
;//se agrega a la pila direccion de buffer y se desreferencia como un char
	push 	ecx
        mov     ecx, [ss: ebp + 6] ; ds:bx = puntero a buffer 
	rol	ecx,16		    	
	lidt    [ds: ecx]          ; carga primer char
	
;//valor del count
	push 	edx
	mov	edx,[ss: ebp + 6]	;	//dejo en algun registro la cantidad a copiar	
 
	int 80h
	pop	edx
	pop	ecx		;libera la pila
	pop	ebx
	pop     eax
	pop     ebp
	retn



