ENTRY(_start)

SECTIONS {
    /* The kernel will start at 1M in memory */
    . = 1M;

    /*
     * We align each section to a page boundary. We place the multiboot header
     * before the text section to ensure that GRUB can find it
     */
    .text : ALIGN(4K) {
    	   *(.multiboot)
    	   *(.text)
    }

    /* TODO: Add in rodata when needed */

    /* All initialized data goes here */
    .data : ALIGN(4K) {
    	   *(.data)
    }

    /* All uninitialized data goes here */
    .bss : ALIGN(4K) {
    	  *(.bss)
    }

    /*
     * Defines the symbol 'end' right after the last section. Note that the
     * value of end is not the current memory address, but the symbol end is
     * placed at the current address in memory.
     */
    end = .;
}
