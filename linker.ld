/*
The bootloader will look at this image and start execution to the symbol designated as the entrypoint.
*/
ENTRY(_start)

/*
Tell where the various sections of the object file will be put in the final kernel image.
*/
SECTIONS
{
    /*
    Use 2 MiB as a start offset.
    */
    . = 2M;

    /*
    Put the multiboot header first or the bootloader won't recognize the file format.
    We'll put the .text section next.
    */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /*
    Read-only data.
    */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /*
    Read-write data (initialized).
    */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /*
    Read-write data (uninitialized) and the stack.
    */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /*
    The compiler may produce other sections, by default it will put them in a segment with the same name.
    Simply add stuff here as needed.
    */
}
