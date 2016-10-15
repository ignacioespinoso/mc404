#ifndef STRUCTURES_DEFINED
#define STRUCTURES_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024
#define MAX_LABEL_SIZE 64

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

//Struct para simbolos definidos pela diretiva .set.
typedef struct Alias {
	char *name;
	unsigned int value;
	struct Alias *next;
} Alias, *Alias_list;

////////////////////////////Funcoes de rotulos//////////////////////////////////
void add_label(char *name, int address, int right, Label_list head_node);

Label_list new_label_list();

Label* find_label(Label_list head_node, char *name);

void print_labels(Label_list head_node);

////////////////////////////Funcoes de simbolos//////////////////////////////////
void add_alias(char *name, unsigned int value, Alias_list head_node);

Alias_list new_alias_list();

Alias* find_alias(Alias_list head_node, char *name);

void print_aliases(Alias_list head_node);

#endif /*STRUCTURES_DEFINED*/
