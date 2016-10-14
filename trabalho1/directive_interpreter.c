#include "directive_interpreter.h"

int directive_verifier(char **string_end, char **directive_parameter) {
	char *string_start = (*string_end);
	bool has_directive = false;

	// Percorre a linha procurando por uma diretiva.
	while(((*string_start) == ' ') && ((*string_start) != '\n') && ((*string_start) != '\0')) {
		string_start++;
	}
	// Caso o primeiro caractere diferente de ' ' seja '.', ha diretiva.
	if(*string_start == '.') {
		has_directive = true;
	}
	printf("String start = %c", *string_start);
	//Verifica se a diretiva eh valida
	if(has_directive) {

		// Encontra o final do nome da diretiva
		for((*string_end) = string_start;
				((**string_end) != ' ') && ((**string_end) != '\n') && ((**string_end) != '\0');
				 (*string_end)++);

		//Cria uma string 'name' que armazena o nome da diretiva.
		char *name = malloc(MAX_SIZE + 1 * sizeof(char));
		int i = 0;
		for(char *probe = string_start ; probe != *string_end; probe++) {
			name[i] = **string_end;
			i++;
		}
		name[i] = '\0';

		return 1;
	} else {
		return 0;
	}
}

bool is_org(char *name) {
	if(strcmp(name, "org") == 0) {
		return true;
	} else {
		return false;
	}
}

bool is_word(char *name) {
	if(strcmp(name, "word") == 0) {
		return true;
	} else {
		return false;
	}

}

bool is_align(char *name) {
	if(strcmp(name, "align") == 0) {
		return true;
	} else {
		return false;
	}
}

bool is_wfill(char *name) {
	if(strcmp(name, "wfill") == 0) {
		return true;
	} else {
		return false;
	}
}

bool is_set(char *name) {
	if(strcmp(name, "set") == 0) {
		return true;
	} else {
		return false;
	}
}

// void apply_org(int *address, char *directive_parameter);
//
// void apply_word(int *address, char *directive_parameter, int **memory_map);
//
// void apply_align(int *address, char *directive_parameter);
//
// void apply_wfill(int *address, int **memory_map, char *directive_parameter);
//
// void apply_set(&aliases, char *directive_parameter);
