#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main() {
    isr_install();
    irq_install();
    clear_screen();
    kprint_at("x86 operating system\n",30,1);
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
        kprint("END - Stopping the CPU\nCLEAR - clear screen\nPAGE - test malloc\nBACKGROUND color - change background color of screen\nnum1 operator num2 - calculator takes two numbers and an operator\n");
    }
    else if(strcmp(input,"CLEAR") == 0)
    {
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
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
    else if (find_char(input, '-') == 1) {
        char num1[20];
        char num2[20];
        get_chars_before_op(input, num1,'-');
        get_chars_after_op(input, num2,'-');
        if (is_numeric(num1) && is_numeric(num2)) {
            int int_num1 = atoi(num1);
            int int_num2 = atoi(num2);
            int result = int_num1 - int_num2;
            kprint("Result: ");
            char result_str[20];
            int_to_ascii(result, result_str);
            kprint(result_str);
        }
    }
    else if (find_char(input, '+') == 1) {
        char num1[20];
        char num2[20];
        get_chars_before_op(input, num1, '+');
        get_chars_after_op(input, num2, '+');
        if (is_numeric(num1) && is_numeric(num2)) {
            int int_num1 = atoi(num1);
            int int_num2 = atoi(num2);
            int result = int_num1 + int_num2; // Change this line to addition
            kprint("Result: ");
            char result_str[20];
            int_to_ascii(result, result_str);
            kprint(result_str);
        }
    }
    else if (find_char(input, '*') == 1) {
        char num1[20];
        char num2[20];
        get_chars_before_op(input, num1, '*');
        get_chars_after_op(input, num2, '*');
        if (is_numeric(num1) && is_numeric(num2)) {
            int int_num1 = atoi(num1);
            int int_num2 = atoi(num2);
            int result = int_num1 * int_num2; // Change this line to multiplication
            kprint("Result: ");
            char result_str[20];
            int_to_ascii(result, result_str);
            kprint(result_str);
        }
    }
    else if (find_char(input, '/') == 1) {
        char num1[20];
        char num2[20];
        get_chars_before_op(input, num1, '/');
        get_chars_after_op(input, num2, '/');
        if (is_numeric(num1) && is_numeric(num2)) {
            int int_num1 = atoi(num1);
            int int_num2 = atoi(num2);

            if (int_num2 != 0) {
                int result = int_num1 / int_num2; // Change this line to division
                kprint("Result: ");
                char result_str[20];
                int_to_ascii(result, result_str);
                kprint(result_str);
            } else {
                kprint("Division by zero is not allowed.");
            }
        }
    }


    else if (strcmp(input, "BACKGROUND RED") == 0) {
        background_color = RED;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND GREEN") == 0) {
        background_color = GREEN;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND BLUE") == 0) {
        background_color = BLUE;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND CYAN") == 0) {
        background_color = CYAN;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND BLACK") == 0) {
        background_color = BLACK;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND MAGENTA") == 0) {
        background_color = MAGENTA;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND BROWN") == 0) {
        background_color = BROWN;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_GRAY") == 0) {
        background_color = LIGHT_GRAY;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND DARK_GRAY") == 0) {
        background_color = DARK_GRAY;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_BLUE") == 0) {
        background_color = LIGHT_BLUE;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_GREEN") == 0) {
        background_color = LIGHT_GREEN;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_CYAN") == 0) {
        background_color = LIGHT_CYAN;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_RED") == 0) {
        background_color = LIGHT_RED;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND LIGHT_MAGENTA") == 0) {
        background_color = LIGHT_MAGENTA;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND YELLOW") == 0) {
        background_color = YELLOW;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else if (strcmp(input, "BACKGROUND WHITE") == 0) {
        background_color = WHITE;
        clear_screen();
        kprint_at("x86 operating system\n",30,1);
    } else {
        kprint("Invalid color choice. try HELP for more info\n");
    }

    kprint("\n>");
}
