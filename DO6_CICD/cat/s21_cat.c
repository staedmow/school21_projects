#include "s21_cat.h"

struct option LONG_OPTIONS[] = {{"number-nonblank", 0, NULL, 'b'},
                                {"number", 0, NULL, 'n'},
                                {"squeeze-blank", 0, NULL, 's'},
                                {NULL, 0, NULL, 0}};  //длинные флаги

int main(int argc, char *argv[]) {
  Options options = {0};
  input(argc, argv, &options);
  open_files(argc - optind, argv + optind, &options);
  return EXIT_SUCCESS;
}

void input(int argc, char *argv[],
           Options *options) {  //функция, где происходит гетопт (поиск флага)
  int options_index = 0;  //определяет последний индекс найденной опции
  char current_option =
      getopt_long(argc, argv, "beEnstTv", LONG_OPTIONS, &options_index);
  while (current_option != -1) {
    set_option(current_option, options);
    current_option =
        getopt_long(argc, argv, "beEnstTv", LONG_OPTIONS, &options_index);
  }
  if (options->b == 1) {
    options->n = 0;
  }
}

void open_files(int file_count, char *file_path[],
                Options *options) {  //поиск и открытие файла
  for (FILE *current_file = NULL; file_count--; ++file_path) {
    current_file = fopen(*file_path, "r");
    if (current_file == NULL) {
      print_error_file(*file_path);
    } else {
      output(current_file, options);
    }
  }
}

void set_option(char option, Options *options) {  //переключение флагов
  switch (option) {
    case 'b':
      options->b = 1;
      break;
    case 'e':
      options->e = 1;
      options->v = 1;
      break;
    case 'E':
      options->e = 1;
      break;
    case 'n':
      options->n = 1;
      break;
    case 's':
      options->s = 1;
      break;
    case 't':
      options->t = 1;
      options->v = 1;
      break;
    case 'T':
      options->t = 1;
      break;
    case 'v':
      options->v = 1;
      break;
    case '?':
    default:
      print_error_option();
  }
}

void output(FILE *file, Options *options) {  //вывод в консоль
  char current_char = fgetc(file);
  while (current_char != EOF) {
    if (options->s && current_char == '\n' && previous_char == '\n') {
      previous_char = current_char;
      current_char = fgetc(file);
      if (current_char != '\n') {
        if (options->e && options->n) {
          printf("%6d\t", count);
          count++;
          printf("$\n");
        } else if (options->n && !options->e) {
          printf("%6d\t", count);
          count++;
          printf("\n");
        } else if (options->e && !options->n) {
          printf("$\n");
        } else {
          printf("\n");
        }
      }
      continue;
    }
    if (options->b && previous_char == '\n' && current_char != '\n') {
      printf("%6d\t", count);
      count++;
    }
    if (options->n && !options->b && previous_char == '\n') {
      printf("%6d\t", count);
      count++;
    }
    if (options->e && current_char == '\n') {
      printf("$");
    }
    if (options->t && current_char == '\t') {
      printf("^");
      current_char = 'I';
    }
    if (options->v && current_char != '\n' && current_char != '\t') {
      reveal_symbols(current_char);
    } else {
      putc(current_char, stdout);
    }
    previous_char = current_char;
    current_char = fgetc(file);
  }
}  //вывод текста в консоль

void reveal_symbols(char current_char) {  //функция для флага v
  if ((signed char)current_char < 0) {
    printf("M-");
    current_char = (signed char)current_char + 128;
    if ((current_char >= 0 && current_char < 32) || current_char == 127) {
      printf("^");
      current_char += 64;
    }
    putc(current_char, stdout);
  } else if (current_char < 32 || current_char == 127) {
    printf("^");
    if (current_char > 126) {
      current_char = current_char - 64;
    } else {
      current_char = current_char + 64;
    }
    putc(current_char, stdout);
  } else {
    putc(current_char, stdout);
  }
}

void print_error_option() {
  fprintf(stdout, "try 'cat --help' for more information.\n");
  exit(EXIT_FAILURE);
}  //при ошибке

void print_error_file(char *file_name) {
  fprintf(stdout, "%s: No such file or directory\n", file_name);
}  //вывод при ошибке
