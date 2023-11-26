# Constants for the multiboot header
.set ALIGN,    1 << 0           # Align loaded modules on page boundaries
.set MEMINFO,  1 << 1           # Provide the memory map
.set FLAGS,    ALIGN | MEMINFO  # Multiboot flag field
.set MAGIC,    0x1BADB002       # ~magic number~ that lets the bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # Checksum to prove we are indeed multiboot

# Declare a header as in the mmultiboot standard
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Kernel entry point
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    # Call the global constructors
    call _init

    # Transfer control to the Kernel
    call kernel_main

    # Hang if kernel_main unexpectedly returns
    cli
1:  hlt
    jmp 1b
.size _start, . - _start
