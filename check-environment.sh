#!/bin/sh

if ! cross_gcc_loc="$(type -p "i686-elf-gcc")" || [[ -z $cross_gcc_loc ]]; then
    echo "cross-compiler not found! make sure it's in your PATH."
fi
