/* mostly stolen from https://wiki.osdev.org/Bare_Bones */

/* constants for the multiboot header */
.set ALIGN,    1 << 0           /* align loaded modules on page boundaries */
.set MEMINFO,  1 << 1           /* provide the memory map */
.set FLAGS,    ALIGN | MEMINFO  /* multiboot flag field */
.set MAGIC,    0x1badb002       /* multiboot *magic* number */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum to prove we are multiboot */

/* declare the multiboot header */
/* the bootloader (probably grub) will find this and say "yeah, this is a kernel" */
.section .multiboot
.align 4           /* the signature must be 32-bit aligned */
.long MAGIC
.long FLAGS
.long CHECKSUM

/* allocate a 16-byte aligned 16KiB stack */
/* (the stack grows downwards on x86) */
.section .bss
.align 16
stack_bottom:      /* create a symbol at the bottom of the stack */
.skip 16384        /* allocate 16,384 bytes */
stack_top:         /* create a symbol at the top of the stack */

/* the bootloader jumps to _start once the kernel is loaded */
.section .text
.global _start
.type _start, @function
_start:
    /* we are now in 32-bit protected mode. */
    /* the bootloader has abandonned us. */
    /* the kernel has absolute control over the machine. */
    /* it can only rely on itself. */

    /* setup the stack pointer to point to the top of the stack */
    /* (remember it grows downwards on x86) */
    mov $stack_top, %esp

    /* TODO: load the GDT here */
    /* TODO: enable paging here */

    /* enter the high-level kernel */
    /* (high-level = c) */
    call kernel_main

    /* now that the system has nothing more to do, put the computer in an infinite loop. */
    cli            /* disable interrupts */
1:  hlt            /* trick the computer into waiting for the next interrupt (they are disabled so it will wait forever) */
    jmp 1b         /* jump to the hlt instruction in case the system wakes up */

/* set the size of the _start symbol to the current location minus its start */
/* useful when debugging */
.size _start, . - _start
