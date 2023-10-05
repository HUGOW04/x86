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
    kprint("You said: ");
    kprint(input);
    kprint("\n>");
}
