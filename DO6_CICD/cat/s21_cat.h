#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE 10  //новая строка

char previous_char = NEWLINE;
int count = 1;

typedef struct Options {
  int b, e, n, s, t, v;
} Options;

void set_option(char option, Options* options);
void open_files(int argc, char* argv[], Options* options);
void print_error_option();
void print_error_file(char* file_name);
void output(FILE* file, Options* options);
void reveal_symbols(char current_symbol);
void input(int file_count, char* file_path[], Options* options);
#endif  // cat
