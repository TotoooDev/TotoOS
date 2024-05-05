#!/bin/sh
# will probably move this to a Makefile later

./check-environment.sh

i686-elf-as boot.asm -o boot.o
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Werror
i686-elf-gcc -T linker.ld -o toto_os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

./check-multiboot.sh
mkdir -p iso/boot/grub
cp toto_os.bin iso/boot/toto_os.bin
cp grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o toto_os.iso iso
