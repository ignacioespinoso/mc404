#ifndef DIRECTIVE_INTERPRETER_DEFINED
#define DIRECTIVE_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int directive_verifier(char **probe, char **directive_parameter);

bool is_org(char *name);

bool is_word(char *name);

bool is_align(char *name);

bool is_wfill(char *name);

bool is_set(char *name);

// void apply_org(int *address, char *directive_parameter);
//
// void apply_word(int *address, char *directive_parameter, int **memory_map);
//
// void apply_align(int *address, char *directive_parameter);
//
// void apply_wfill(int *address, int **memory_map, char *directive_parameter);
//
// void apply_set(&aliases, char *directive_parameter);


#endif /*DIRECTIVE_INTERPRETER_DEFINED*/
