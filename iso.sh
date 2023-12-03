#!/bin/bash

set -e
. ./build.sh

mkdir -p iso
mkdir -p iso/boot
mkdir -p iso/boot/grub

cp sysroot/usr/boot/TotoOS.kernel iso/boot/TotoOS.kernel
cat > iso/boot/grub/grub.cfg << EOF
menuentry "TotoOS" {
    multiboot /boot/TotoOS.kernel
}
EOF

grub-mkrescue -o TotoOS.iso iso
