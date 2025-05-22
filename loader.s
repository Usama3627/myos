.section .multiboot
.align 4
.long 0x1BADB002
.long 0x00
.long -(0x1BADB002)

.section .text
.global _start
.extern kmain

_start:
    mov $stack_top, %esp

    call kmain

hang:
    cli
hlt_loop:
    hlt
    jmp hlt_loop

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:
.section .note.GNU-stack,"",@progbits
