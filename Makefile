# Disable implicit rules
.SUFFIXES:
MAKEFLAGS += --no-builin-rules

BUILDDIR := build
SRCDIR := src
OBJDIR := obj
_OBJS := loader.o kernel.o screen.o portio.o
OBJS := $(patsubst %,$(OBJDIR)/%,$(_OBJS))

OUTDIR := out
ISODIR := $(OUTDIR)/iso
KBIN := $(OUTDIR)/kernel.bin

IMG := $(OUTDIR)/gulbuntu.iso

# Toolchain and flags
ASM := nasm
CC := /usr/local/cross/bin/gcc
ASMFLAGS := -felf
CFLAGS := -std=gnu99 -ffreestanding -Wall -Werror -m32 -Iinclude -g
LDFLAGS := -ffreestanding -nostdlib -lgcc -T $(BUILDDIR)/linker.ld -m32

all: $(IMG)

# Create a bootable image
$(IMG): $(KBIN)
	mkdir -p $(ISODIR)/boot/grub
	cp $(BUILDDIR)/grub/grub.cfg $(ISODIR)/boot/grub
	cp $(KBIN) $(ISODIR)/boot
	grub-mkrescue -o $(IMG) $(ISODIR)

# Link all object files to the kernel binary
$(KBIN): $(OBJS) | $(OUTDIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(KBIN)

# Assemble loader.s
$(OBJDIR)/%.o: $(SRCDIR)/boot/%.s | $(OBJDIR)
	$(ASM) $(ASMFLAGS) -o $@ $<

# Compile all C source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create the out directory if it doesn't exist
$(OUTDIR):
	mkdir -p $(OUTDIR)

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(OUTDIR)