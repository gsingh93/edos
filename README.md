Gulbuntu OS
===========

This is a toy OS made by Gulshan Singh.

This was built with a GCC 4.8.0 cross compiler. Building without a cross compiler may not work. See (this link)[http://wiki.osdev.org/GCC_Cross-Compiler] to see how to build a cross compiler.

To build, type make. This will generate a bootable ISO at out/gulbuntu.iso

grub-mkrescue and xorriso are required packages for making the ISO

You can run the ISO using qemu. The emulate.sh script should run qemu with the correct command line options

I will try to get more documentation out soon so that others can learn from this OS.