#ifndef INSTRUCTION_INTERPRETER_DEFINED
#define INSTRUCTION_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#define MAX_SYMBOL_SIZE 64

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "structures.h"

int instruction_applier(char **string_end, Label_list label_head_node, int *address
												, char **memory_map, int *right, int line_counter
												, bool *be_printed, FILE *output);


#endif /*INSTRUCTION_INTERPRETER_DEFINED*/
