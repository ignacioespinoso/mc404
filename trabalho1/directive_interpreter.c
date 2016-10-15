#include "directive_interpreter.h"

///////////Verifica se existe diretiva e argumentos da mesma validos////////////
int directive_verifier(char *string_end, char *directive_parameter) {
	char *string_start = string_end;
	bool has_directive = false;

	// Percorre a linha procurando por uma diretiva.
	while(((*string_start) == ' ') && ((*string_start) != '\n') && ((*string_start) != '\0')) {
		(*string_start)++;
	}
	// Caso o primeiro caractere diferente de ' ' seja '.', ha diretiva.
	if(*string_start == '.') {
		has_directive = true;
	}

	//Verifica se a diretiva eh valida
	if(has_directive) {
		string_start++;

		// Encontra o final do nome da diretiva
		for(string_end = string_start;
				((*string_end) != ' ') && ((*string_end) != '\n') && ((*string_end) != '\0');
				 string_end++);
		//Cria uma string 'name' que armazena o nome da diretiva.
		char *name = malloc(MAX_SIZE + 1 * sizeof(char));
		int i = 0;
		for(char *probe = string_start ; probe != string_end; probe++, i++) {
			name[i] = *probe;
		}
		name[i] = '\0';
		//Verifica se o nome da diretiva eh valido. Nao verifica se os parametros sao validos.
		//Caso seja uma diretiva valida, retorna um valor positivo.
		int value_return = -1;
		if(is_org(name)) {
			value_return = 1;
		} else if(is_word(name)) {
			value_return = 2;
		} else if(is_align(name)) {
			value_return = 3;
		} else if(is_wfill(name)) {
			value_return = 4;
		} else if(is_set(name)) {
			value_return = 5;
		}
		free(name);

		//Encontra o parametro da diretiva e o salva em directive_parameter.
		while(((*string_end) == ' ') && ((*string_end) != '\n') && ((*string_end) != '\0')) {
			string_end++;
		}
		if((*string_end) != '\0') {
			//String_start armazena o comeco do parametro.
			string_start = string_end;
			//String_end armazena o final do parametro.
			while(((*string_end) != ' ') && ((*string_end) != '\n') && (*string_end != '\0')) {
				string_end++;
			}
			int i = 0;
			for(char *probe = string_start ; probe != string_end; probe++, i++) {
				*(directive_parameter + i) = *probe;
			}
			directive_parameter[i] = '\0';
			printf("A diretiva tem parametro ===%s===\n", (directive_parameter));
		} else {
			value_return = -1;
		}

		return value_return;
	} else {
		return 0;
	}
}

///////////////////Metodos de verificacao de nome da diretiva///////////////////
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

//////Metodos de aplicacao das diretivas e avaliacao dos seus parametros////////
//Os metodos retornam true para uma aplicacao bem sucedida e false caso contrario.
bool apply_org(int *address, char *directive_parameter) {
	char *string_start = directive_parameter;
	int base = find_base(string_start);
	int value;
	if(base == 10) {
		printf("1\n");
		value = strtol(directive_parameter, &string_start, 10);
	} else if(base == 16) {
		printf("2\n");
		value = strtol(directive_parameter, &string_start, 16);
	} else {
		printf("3\n");
		return false;
	}
	printf("value = %d\n", value);
	return true;
}

// bool apply_word(int *address, char *directive_parameter, int **memory_map);
//
// bool apply_align(int *address, char *directive_parameter);
//
// bool apply_wfill(int *address, int **memory_map, char *directive_parameter);
//
// bool apply_set(&aliases, char *directive_parameter);
