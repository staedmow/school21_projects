#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int e, i, v, c, l, n, h, s, f, o;
  char* pattern;
  int length_pattern;
  int memory_pattern;
} options;

void pattern_add(options* arg, char* pattern) {
  if (arg->length_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    arg->memory_pattern = 1024;
  }
  if (arg->length_pattern != 0) {
    strcat(arg->pattern + arg->length_pattern, "|");
    arg->length_pattern++;
  }
  arg->length_pattern +=
      sprintf(arg->pattern + arg->length_pattern, "(%s)", pattern);
}

void add_reg_from_file(
    options* arg, char* filepath) {  // Добавление регулярных выражений из файла
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    perror(filepath);
    exit(1);
  }
  char line[10000];
  int read;
  while (fgets(line, sizeof(line), f) != NULL) {
    read = strlen(line);
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_add(arg, line);
  }
  fclose(f);
}

options option_parser(int argc,
                      char* argv[]) {  // Парсер опций командной строки
  options arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.length_pattern == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) arg.h = 1;
  return arg;
}

void output_line(char* line, int n) {  // Вывод строки
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(
    regex_t* re,
    char* line) {  // Поиск и вывод совпадений с регулярным выражением в строке
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(options arg, char* path, regex_t* reg) {  // Обработка файла
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    perror(path);
    exit(1);
  }
  int line_count = 1;
  int c = 0;
  int read;
  char line[10000];
  while (fgets(line, sizeof(line), f) != NULL) {
    read = strlen(line);
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line, read);
        }
      }
      c++;
    }
    line_count++;
  }

  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg.l && c > 0) printf("%s\n", path);
  fclose(f);
}

void output(options arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char** argv) {
  options arg = option_parser(argc, argv);  // Парсинг опций из командной строки
  output(arg, argc, argv);  // Вывод результатов
  free(arg.pattern);  // Освобождение памяти, выделенной для хранения
                      // регулярного выражения
  return 0;
}