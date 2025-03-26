#include "s21_grep.h"

void print_match(regex_t* reg, char* line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(reg, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) putchar(line[i]);
    putchar('\n');
    offset += match.rm_eo;
  }
}

void template(arguments* arg, char* v_temp) {
  if (arg->pattern != 0) {
    strcat(arg->v_temp + arg->pattern, "|");
    arg->pattern++;
  }
  arg->pattern += sprintf(arg->v_temp + arg->pattern, "(%s)", v_temp);
}

void add_ref_from_file(arguments* arg, char* path) {
  FILE* f = fopen(path, "r");
  if (f == NULL && !arg->s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", path);
    return;
  }

  char* line = NULL;
  size_t memlen = 0;
  int read = getline(&line, &memlen, f);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    template(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

arguments arguments_parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        template(&arg, optarg);
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
      case 's':
        arg.s = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 'f':
        arg.f = 1;
        add_ref_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        break;
    }
  }
  if (arg.pattern == 0) {
    template(&arg, argv[optind]);
    optind++;
  }
  if ((argc - optind) == 1) {
    arg.h = 1;
  }
  return arg;
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void processFile(arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL && !arg.s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", path);
    return;
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_count = 1;
  int counter = 0;
  read = getline(&line, &memlen, f);

  while (read != -1) {
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
      counter++;
    }

    read = getline(&line, &memlen, f);
    line_count++;
  }
  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", counter);
  }
  if (arg.l && counter > 0) printf("%s\n", path);
  fclose(f);
}

void output(arguments arg, int argc, char* argv[]) {
  regex_t re;
  int error = regcomp(&re, arg.v_temp, REG_EXTENDED | arg.i);
  if (error) {
    fprintf(stderr, "grep: invalid regular expression: %d\n", arg.pattern);
    return;
  }
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char* argv[]) {
  arguments arg = arguments_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}