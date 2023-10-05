#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main() {
    isr_install();
    irq_install();

    kprint(">");
}

void user_input(char* input)
{
    if(strcmp(input,"END") == 0)
    {
        kprint("Stopping the CPU\n");
        asm volatile("hlt");
    }
    else if(strcmp(input,"HELP") == 0)
    {
        kprint("END - Stopping the CPU\nCLEAR - clear screen\n");
    }
    else if(strcmp(input,"CLEAR") == 0)
    {
        clear_screen();
    }
    else if (strcmp(input, "PAGE") == 0) {
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n>");
}
