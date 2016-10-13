#ifndef LABEL_INTERPRETER_DEFINED
#define LABEL_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//Struct que define um rotulo.
//Right = 1 faz referencia que o rotulo se refere a palavra direita da memoria.
//Right = -1 faz referencia que o rotulo se refere a palavra esquerda da memoria.
typedef struct Label {
	char *name;
	int address;
	int right;
	struct Label *next;
} Label, *Label_list;

int label_verifier(char *line, Label_list head_node, char **string_end);

void add_label(char *name, int address, int right, Label_list head_node);

void new_label_list(Label_list *head_node);

void print_labels(Label_list head_node);

#endif /*LABEL_INTERPRETER_DEFINED*/
