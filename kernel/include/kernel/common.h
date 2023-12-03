#ifndef _KERNEL_COMMON_H
#define _KERNEL_COMMON_H

#include <stdint.h>
#include <stdbool.h>

static inline uint32_t far_peek(uint16_t sel, void* offset) {
    uint32_t ret;
    __asm__(
        "push %%fs\n\t"
        "mov %1, %%fs\n\t"
        "mov %%fs:(%2), %0\n\t"
        "pop %%fs"
        : "=r"(ret)
        : "g"(sel), "r"(offset)
    );
    return ret;
}

static inline void far_poke(uint16_t sel, void* offset, uint8_t v) {
    __asm__(
        "push %%fs\n\t"
        "mov %0, %%fs\n\t"
        "movb %2, %%fs:(%1)\n\t"
        "pop %%fs"
        :
        : "g"(sel), "r"(offset), "r"(v)
    );
}

static inline void port_out(uint16_t port, uint8_t val) {
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(val), "Nd"(port)
        : "memory"
    );
}

static inline uint8_t port_in(uint16_t port) {
    uint8_t ret;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(ret)
        : "Nd"(port)
        : "memory"
    );
    return ret;
}

static inline void io_wait(void) {
    port_out(0x80, 0);
}

static inline bool are_interrupts_enabled(void) {
    uint32_t flags;
    __asm__ volatile (
        "pushf\n\t"
        "pop %0"
        : "=g"(flags)
    );
    return flags & (1 << 9);
}

static inline uint32_t save_irq_disable(void) {
    uint32_t flags;
    __asm__ volatile (
        "pushf\n\t"
        "cli\n\t"
        "pop %0"
        : "=r"(flags)
        :
        : "memory"
    );
    return flags;
}

static inline void irq_restore(uint32_t flags) {
    __asm__(
        "push %0\n\t"
        "popf"
        :
        : "rm"(flags)
        : "memory", "cc"
    );
}

static inline void new_idt(void* base, uint16_t size) {
    struct {
        uint16_t length;
        void* base;
    } __attribute__((packed)) IDTR = { size, base };

    __asm__(
        "lidt %0"
        :
        : "m"(IDTR)
    );
}

#endif