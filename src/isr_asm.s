%macro ISR_NOERRCODE 1
		global isr%1
    isr%1:
		cli
		push byte 0				; Dummy error code
		push byte %1
		jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
		global isr%1
    isr%1:
		cli
		push %1					; Error code was pushed before this
		jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17	
ISR_NOERRCODE 18	
ISR_NOERRCODE 19	
ISR_NOERRCODE 20	
ISR_NOERRCODE 21	
ISR_NOERRCODE 22	
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25	
ISR_NOERRCODE 26	
ISR_NOERRCODE 27	
ISR_NOERRCODE 28
ISR_NOERRCODE 29	
ISR_NOERRCODE 30	
ISR_NOERRCODE 31

extern isr_handler				; Defined in isr.c
isr_common_stub:
		pusha					; Push all general purpose registers
		push ds					; Push all data segment registers
		push es
		push fs
		push gs
		mov ax, 0x10			; Load the kernel data segment descriptor
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		call isr_handler	; Handle the ISR
		pop eax					
		pop gs					; Restore all regs modified in this function
		pop fs
		pop es
		pop ds
		popa
		add esp, 8				; Removes the pushed error code and ISR number
		iret					; Return from interrupt
		
