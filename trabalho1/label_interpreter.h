#ifndef LABEL_INTERPRETER_DEFINED
#define LABEL_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024
#define MAX_LABEL_SIZE 64

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "structures.h"

int label_verifier(char *line, char **string_end, char *label_name, Label_list head_node);

#endif /*LABEL_INTERPRETER_DEFINED*/
