all: kernel.elf

kernel.elf: loader.o kmain.o
	ld -T link.ld -melf_i386 loader.o kmain.o -o kernel.elf

kmain.o: kmain.c
	gcc -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -c kmain.c -o kmain.o

loader.o: loader.s
	as --32 loader.s -o loader.o

iso: kernel.elf grub.cfg
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso -d /usr/lib/grub/i386-pc

run: iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -f *.o kernel.elf os.iso
	rm -rf iso
