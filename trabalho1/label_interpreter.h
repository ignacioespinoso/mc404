#ifndef LABEL_INTERPRETER_DEFINED
#define LABEL_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Label {
	char name;
	int address;
	struct Label *next;
} Label, *Label_list;

char* label_verifier(char *line, int line_counter);

void add_label(char *name, int address, Label_list start);
#endif /*LABEL_INTERPRETER_DEFINED*/
