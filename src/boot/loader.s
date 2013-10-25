;;; Globals and externs
global _start                   ; Loader entry point needed by linker
extern kmain                    ; Defined in kernel.c

;;; Constants
MAGIC       equ 0x1BADB002      ; Multiboot magic number
FLAGS       equ 0               ; No multiboot flags
CHECKSUM    equ -(MAGIC + FLAGS)

;;; Multiboot header required by grub
section .multiboot
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

;;; Our loader will start the kernel
section .text
_start:
        call kmain
        cli                     ; Disable interrupts (clear interrupts)
;;; Go into an infinite loop if kernel returns
loop:
        hlt                     ; Halt the CPU
        jmp loop                ; If an interrupt wakes the CPU, halt it again

