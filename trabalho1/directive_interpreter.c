#include "directive_interpreter.h"

int directive_verifier(char **string_end, char **directive_parameter) {
	char *string_start = *(*string_end);

	// Percorre a linha procurando por uma diretiva.
	// Caso o primeiro caractere diferente de ' ' seja '.', ha diretiva.
	while((*string_start) == ' ') {
		string_start++;
	}
	if(string_start != ' ')


	bool has_directive = false, directive_error = false;

	int j = 0;
	for(j = 0; (j < (MAX_SIZE-1)) && (line[j] != ':') && (line[j] != '\n'); j++);

	//Apos a verificacao de atribuicao impropria de rotulos...
	if(line[j]== ':') {
		(*string_end) = line + j;
		has_label = true;

		//Caso algum caractere nao seja alfanumerico ou underscore, ha erro da label.
		char *verifier = string_start;
		while(verifier != (*string_end)) {
			if(!isalnum(*verifier) && (*verifier != '_')) {
				label_error = true;
			}
			verifier++;
		}

		//Verifica se o primeiro caractere eh um numero.
		if(isdigit(*string_start)) {
			label_error = true;
		}

		//Verifica se logo apos os dois pontos (":") ha algum caractere.
		if((*((*string_end) + 1) != ' ') && (*((*string_end) + 1) != '\t') && (*((*string_end) + 1) != '\n')) {
			label_error = true;
		}
	}
}

bool is_org(char *name);

bool is_word(char *name);

bool is_align(char *name);

bool is_wfill(char *name);

bool is_set(char *name);

void apply_org(int *address, char *directive_parameter);

void apply_word(int *address, char *directive_parameter, int **memory_map);

void apply_align(int *address, char *directive_parameter);

void apply_wfill(int *address, int **memory_map, char *directive_parameter);

void apply_set(&aliases, char *directive_parameter);
