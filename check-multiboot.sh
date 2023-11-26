#!/bin/bash

if grub-file --is-x86-multiboot bin/TotoOS.bin; then
    echo "Multiboot ready!"
else
    echo "The file is not multiboot :("
fi
