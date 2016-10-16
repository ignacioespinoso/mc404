#ifndef DIRECTIVE_INTERPRETER_DEFINED
#define DIRECTIVE_INTERPRETER_DEFINED

#define MAX_SIZE 4097
#define MAX_SYMBOL_SIZE 64

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "structures.h"

int directive_verifier(char **probe, char *directive_parameter, int line_counter);

///////////////////Metodos de verificacao de nome da diretiva///////////////////
bool is_org(char *name);

bool is_word(char *name);

bool is_align(char *name);

bool is_wfill(char *name);

bool is_set(char *name);

//////Metodos de aplicacao das diretivas e avaliacao dos seus parametros////////
//Os metodos retornam true para uma aplicacao bem sucedida e false caso contrario.
bool apply_org(int *address, char *directive_parameter, int line_counter);

bool apply_word(int *address, char *directive_parameter, char **memory_map
								, Label_list label_head_node, Alias_list alias_head_node, bool *be_printed, int line_counter);

bool apply_align(int *address, char *directive_parameter, int line_counter);

bool apply_wfill(int *address, char *directive_parameter, char **memory_map, char **string_end
								, Label_list label_head_node, Alias_list alias_head_node, bool *be_printed, int line_counter);

bool apply_set(Alias_list head_node, char *directive_parameter
								, char **string_end, Label_list label_head_node, int line_counter);

#endif /*DIRECTIVE_INTERPRETER_DEFINED*/
