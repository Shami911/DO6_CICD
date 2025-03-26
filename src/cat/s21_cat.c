#include "s21_cat.h"

arguments argument_parser(int argc, char* argv[]) {
  arguments arg = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      default:
        fprintf(stderr, "Unknown option");
        break;
    }
  }
  return arg;
}

void v_output(char ch) {
  if (!isprint(ch) && !isascii(ch)) {
    putchar('M');
    putchar('-');
    ch = toascii(ch);
  }
  if (iscntrl(ch) && ch != '\n') {
    putchar('^');
    putchar((ch) == 127 ? '?' : ch + 64);
  }
}

void outline(arguments* arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t')
      printf("^I");
    else {
      if (arg->E && line[i] == '\n') putchar('$');
      if (arg->v && line[i] != '\n' && line[i] != '\t' && (!isprint(line[i]))) {
        v_output(line[i]);
      } else
        putchar(line[i]);
    }
  }
}

void output(arguments* arg, char* argv[], int argc) {
  int line_count = 1;
  int empty_count = 0;
  for (int i = optind; i < argc; i++) {
    FILE* f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
    } else {
      char* line = NULL;
      size_t memline = 0;
      int read = 0;

      read = getline(&line, &memline, f);

      while (read != -1) {
        if (line[0] == '\n')
          empty_count++;
        else
          empty_count = 0;
        if (arg->s && empty_count > 1) {
          empty_count -= 1;
        } else {
          if (arg->b && line[0] != '\n') {
            printf("%6d\t", line_count);
            line_count++;
          } else if (arg->n) {
            printf("%6d\t", line_count);
            line_count++;
          }

          outline(arg, line, read);
        }
        read = getline(&line, &memline, f);
      }

      free(line);
      fclose(f);
    }
  }
}

int main(int argc, char* argv[]) {
  arguments arg = argument_parser(argc, argv);
  output(&arg, argv, argc);
  return 0;
}