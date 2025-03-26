#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, n, s, e, E, T, v;
} arguments;

arguments argument_parser(int argc, char* argv[]);
void v_output(char ch);
void outline(arguments* arg, char* line, int n);
void output(arguments* arg, char* argv[], int argc);

#endif
