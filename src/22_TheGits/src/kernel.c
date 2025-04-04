#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "libc/stdarg.h"
#include "libc/gdt.h" 
#include "libc/scrn.h"
#include "libc/idt.h"
#include "libc/isr_handlers.h"
#include "libc/irq.h"



struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    init_gdt();
    printf("Hello, World!\n");
    remap_pic();
    init_idt();
    init_irq();

    // Aktiver interrupts
    __asm__ volatile ("sti");
    __asm__ volatile ("int $0x80");

    while (1) {
        __asm__ volatile ("hlt");
    }

    return 0;
}