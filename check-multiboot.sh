#!/bin/sh

if grub-file --is-x86-multiboot toto_os.bin; then
    echo "multiboot ready!"
else
    echo "your kernel is not multiboot compliant!"
fi
