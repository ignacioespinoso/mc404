#include "directive_interpreter.h"

///////////Verifica se existe diretiva ///////////////////////
//Obtem o primeiro parametro da diretiva, mas nao o avalia.
int directive_verifier(char **string_end, char *directive_parameter) {
	char *string_start = *string_end;
	bool has_directive = false;

	// Percorre a linha procurando por uma diretiva.
	while(((*string_start == ' ') || (*string_start == '\t')) && ((*string_start) != '\n') && ((*string_start) != '\0')) {
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
		for(*string_end = string_start;
				((**string_end) != ' ') && ((**string_end) != '\t') && ((**string_end) != '\n') && ((**string_end) != '\0');
				 (*string_end)++);
		//Cria uma string 'name' que armazena o nome da diretiva.
		char *name = malloc((MAX_SYMBOL_SIZE + 1) * sizeof(char));
		int i = 0;
		for(char *probe = string_start ; probe != *string_end; probe++, i++) {
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

		if(value_return != -1) {
			//Encontra o parametro da diretiva e o salva em directive_parameter.
			while(((**string_end == ' ') || (**string_end == '\t')) && ((**string_end) != '\n') && ((**string_end) != '\0')) {
				(*string_end)++;
			}

			//Caso o primeiro caractere, nao sendo espaco, nao seja o final do arquivo
			// , eh iniciada a determinacao do parametro
			if((**string_end) != '\0') {
				//String_start armazena o comeco do parametro.
				string_start = *string_end;
				//String_end armazena o final do parametro.
				while(((**string_end) != ' ') && ((**string_end) != '\t')
								&& ((**string_end) != '\n') && (**string_end != '\0')) {
					(*string_end)++;
				}
				int i = 0;
				for(char *probe = string_start ; probe != *string_end; probe++, i++) {
					*(directive_parameter + i) = *probe;
				}
				directive_parameter[i] = '\0';
				printf("A diretiva tem parametro ===%s===\n", (directive_parameter));
			} else {
				value_return = -1;
			}
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

	//Verifica se o primeiro caractere do simbolo eh um numero.
	if(isdigit(directive_parameter[0])) {
		return false;
	}

	if(base == 10) {
		printf("1\n");
		value = strtol(directive_parameter, &string_start, 10);
	} else if(base == 16) {
		value = strtol(directive_parameter, &string_start, 16);
	} else {
		return false;
	}
	//Sendo um parametro valido, atualiza o endereco atual.
	*address = value;
	printf("value = %x\n", value);
	return true;
}

// bool apply_word(int *address, char *directive_parameter, int **memory_map) {
// 	//Avalia endereco invalido
// 	if((*address > 1024) || (*address < 0)) {
// 		return -1;
// 	}
// 	int base = find_base(directive_parameter);
// 	if(base == 10) {
//
// 	} else if (base == 16) {
//
// 	} else {
//
// 	}
// }

bool apply_align(int *address, char *directive_parameter) {
	char *string_start = directive_parameter;
	if(find_base(string_start) == 10) {
		int value = strtol(directive_parameter, &string_start, 10);
		while((*address) % value != 0) {
			(*address)++;
		}
		return true;
	} else {
		return false;
	}
}

// bool apply_wfill(int *address, int **memory_map, char *directive_parameter);
//
bool apply_set(Alias_list head_node, char *directive_parameter
								, char **string_end, Label_list label_head_node) {
	//String_start armazena o comeco do segundo parametro.
	char *string_start = *string_end;
	//Encontra o segundo parametro da diretiva.
	while(((*string_start == ' ') || (*string_start == '\t')) && ((*string_start) != '\n') && (*string_start != '\0')) {
		(*string_end)++;
		string_start++;
	}

	//String_end armazena o final do segundo parametro.
	while(((**string_end) != ' ') && ((**string_end) != '\t') && ((**string_end) != '\n') && (**string_end != '\0')) {
		(*string_end)++;
	}

	//Caso nao haja segundo parametro, ha erro.
	if(((*string_start) == '\n') || ((*string_start) == '\0')) {
		return false;
	}

	//Armazena os valores entre o string_end e string_start em parameter_2.
	bool valid_parameter = true;
	char *parameter_2 = malloc(MAX_SIZE + 1 * sizeof(char));
	int i = 0;
	for(char *probe = string_start ; probe != *string_end; probe++, i++) {
		parameter_2[i] = *probe;
	}
	parameter_2[i] = '\0';

	//Avalia o primeiro parametro, que equivale ao simbolo.
	for(int i = 0; i < strlen(directive_parameter); i++) {
		if(!isalnum(directive_parameter[i]) && (directive_parameter[i] != '_')) {
			valid_parameter = false;
		}
	}
	//Verifica se ha um simbolo com mesmo nome na lista.
	for(Alias *probe = head_node; probe && valid_parameter; probe=probe->next) {
		if(strcmp(probe->name, directive_parameter) == 0) {
			valid_parameter = false;
		}
	}
	//Verifica se ha um rotulo com mesmo nome.
	for(Label *probe = label_head_node; probe && valid_parameter; probe=probe->next) {
		if(strcmp(probe->name, directive_parameter) == 0) {
			valid_parameter = false;
		}
	}
	//Avalia o segundo parametro, que equivale ao valor do simbolo.
	int value;
	printf("Parametro 1 =%s=, Parametro 2 =%s=\n", directive_parameter, parameter_2);
	int base = find_base(parameter_2);
	char *pointer_end;
	if(base == 10) {
		printf("Base 10\n");
		value = strtol(parameter_2, &pointer_end, 10);
	} else if(base == 16) {
		printf("Base 16\n");
		value = strtol(parameter_2, &pointer_end, 16);
	} else {
		printf("Base com erro\n");
		valid_parameter = false;
	}

	if(valid_parameter) {
		add_alias(directive_parameter, value, head_node);
		return true;
	} else {
		return false;
	}
}
