#include "string.h"
#include "../cpu/type.h"

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    s32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/* K&R 
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int atoi(char *string)
{
    char a=0;
    int res=0;
    while((a= *string++)!='\0')
        {        
            res = res*10 + a - '0';  
        }

    return res;
}

int is_numeric(const char* str) {
    int i = 0;

    // Check if the string is empty
    if (str[0] == '\0') {
        return 0;
    }

    // Check each character in the string
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0; // Non-numeric character found
        }
        i++;
    }

    return 1; // All characters are numeric
}

int find_char(const char* str, char target) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == target) {
            return 1; // Return 1 if the character was found
        }
    }
    return 0; // Return 0 if the character was not found
}

void get_chars_before_op(const char* input, char* output,const char* op) {
    int i;

    for (i = 0; input[i] != '\0' && input[i] != op; i++) {
        output[i] = input[i];
    }

    output[i] = '\0'; // Null-terminate the output string
}

void get_chars_after_op(const char* input, char* output,const char* op) {
    int i, j;

    // Find the position of the first '-' character in the input
    for (i = 0; input[i] != '\0' && input[i] != op; i++) {
        // Continue until the '-' character is found
    }

    // Skip the '-' character and copy characters after it to the output
    if (input[i] == op) {
        i++; // Skip the '-'
    }

    for (j = 0; input[i] != '\0'; i++, j++) {
        output[j] = input[i];
    }

    output[j] = '\0'; // Null-terminate the output string
}
