#ifndef STRUCTURES_DEFINED
#define STRUCTURES_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024
#define MAX_LABEL_SIZE 64
#define MNEMONICS_AMOUT 17

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

//Verifica a string, retornando a base (caso seja uma string valida) e -1 caso contrario.
int find_base(char *string_start);

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

/////////////////////Funcoes dos mnemonicos/////////////////////////////////////
//Cria uma nova lista de mnemonicos
char** new_mnemonic_list();

//Compara o mnemonico dado com a lista, retornando um valor positivo caso o mnemonico seja valido.
int find_mnemonic(char *mnemonic, char **mnemonic_list);
#endif /*STRUCTURES_DEFINED*/
