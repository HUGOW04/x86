#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int atoi(char *string);
int is_numeric(const char* str);
int find_char(const char* str, char target);
void get_chars_before_op(const char* input, char* output,const char* op);
void get_chars_after_op(const char* input, char* output,const char* op);

#endif
