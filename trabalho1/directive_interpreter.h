#ifndef DIRECTIVE_INTERPRETER_DEFINED
#define DIRECTIVE_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#define MAX_SYMBOL_SIZE 64

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "argument_manipulator.h"
#include "structures.h"

int directive_verifier(char **probe, char *directive_parameter);

///////////////////Metodos de verificacao de nome da diretiva///////////////////
bool is_org(char *name);

bool is_word(char *name);

bool is_align(char *name);

bool is_wfill(char *name);

bool is_set(char *name);

//////Metodos de aplicacao das diretivas e avaliacao dos seus parametros////////
//Os metodos retornam true para uma aplicacao bem sucedida e false caso contrario.
bool apply_org(int *address, char *directive_parameter);

// bool apply_word(int *address, char *directive_parameter, int **memory_map);
//
bool apply_align(int *address, char *directive_parameter);

// bool apply_wfill(int *address, int **memory_map, char *directive_parameter);
//
bool apply_set(Alias_list head_node, char *directive_parameter
								, char **string_end, Label_list label_head_node);

#endif /*DIRECTIVE_INTERPRETER_DEFINED*/
