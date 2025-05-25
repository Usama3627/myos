# Makefile for MyOS Kernel
# Supports modular kernel structure with multiple source files

# Compiler and linker settings
CC = gcc
AS = as
LD = ld
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -Ikernel
ASFLAGS = --32
LDFLAGS = -T link.ld -melf_i386

# Source files
KERNEL_SOURCES = kernel/main.c kernel/screen.c kernel/input.c kernel/utils.c
KERNEL_OBJECTS = $(KERNEL_SOURCES:.c=.o)
ASM_SOURCES = loader.s
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)

# All object files
OBJECTS = $(ASM_OBJECTS) $(KERNEL_OBJECTS)

# Default target
all: kernel.elf

# Build the kernel ELF file
kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

# Compile C source files
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble assembly source files
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# Create ISO image
iso: kernel.elf grub.cfg
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso -d /usr/lib/grub/i386-pc

# Run the kernel in QEMU
run: iso
	qemu-system-i386 -cdrom os.iso

# Debug target - run with GDB support
debug: iso
	qemu-system-i386 -cdrom os.iso -s -S

# Clean build artifacts
clean:
	rm -f $(OBJECTS) kernel.elf os.iso
	rm -rf iso

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the kernel (default)"
	@echo "  iso     - Create bootable ISO image"
	@echo "  run     - Build and run in QEMU"
	@echo "  debug   - Run with GDB debugging support"
	@echo "  clean   - Remove all build artifacts"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all iso run debug clean help
