#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 4096

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char v_temp[SIZE];
  char pattern;
} arguments;

void print_match(regex_t* reg, char* line);
void template(arguments* arg, char* v_temp);
void add_ref_from_file(arguments* arg, char* path);
arguments arguments_parser(int argc, char* argv[]);
void output_line(char* line, int n);
void processFile(arguments arg, char* path, regex_t* reg);
void output(arguments arg, int argc, char* argv[]);

#endif