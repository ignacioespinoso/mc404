#include "directive_interpreter.h"

///////////Verifica se existe diretiva ///////////////////////
//Obtem o primeiro parametro da diretiva, mas nao o avalia.
int directive_verifier(char **string_end, char *directive_parameter, int line_counter) {
	char *string_start = *string_end;
	bool has_directive = false;

	// Percorre a linha procurando por uma diretiva.
	while(((*string_start == ' ') || (*string_start == '\t')) && ((*string_start) != '\n') && ((*string_start) != '\0')) {
		string_start++;
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
bool apply_org(int *address, char *directive_parameter, int line_counter) {
	char *string_start = directive_parameter;
	int base = find_base(string_start);
	int value;

	if(base == 10) {
		value = strtol(directive_parameter, &string_start, 10);
	} else if(base == 16) {
		if(strlen(directive_parameter) != 12) {
			printf("ERROR on line %d\n", line_counter);
			printf("Valor hexadecimal invalido!\n");
			return false;
		}
		value = strtol(directive_parameter, &string_start, 16);
	} else {
		printf("ERROR on line %d\n", line_counter);
		printf("Valor invalido!\n");
		return false;
	}
	//Sendo um parametro valido, atualiza o endereco atual.
	*address = value;
	return true;
}

bool apply_word(int *address, char *directive_parameter, char **memory_map
								, Label_list label_head_node, Alias_list alias_head_node, bool *be_printed, int line_counter) {

	//Avalia o tamanho do endereco
	if((*address > 1024) || (*address < 0)) {
		printf("ERROR on line %d\n", line_counter);
		printf("Endereco invalido!\n");
		return false;
	}
	int base = find_base(directive_parameter);
	char *int_end;
	//Caso o parametro nao possua uma base valida, eh feita verificacao para rotulos e simbolos.
	if(be_printed) {
		if(base == -1) {
			Label *token = find_label(label_head_node, directive_parameter);
			Alias *symbol = find_alias(alias_head_node, directive_parameter);
			if(token) {
				int value = token->address;
					sprintf((memory_map[*address]), "%010X", value);

			} else if(symbol) {
				unsigned int value = symbol->value;
					sprintf((memory_map[*address]), "%010X", value);
			} else {
				printf("ERROR on line %d\n", line_counter);
				printf("Valor de escrita invalido!\n");
				return false; //O parametro nao eh um nem um numero nem um simbolo nem um rotulo.
			}
		} else {
			if(base == 10) {
				int value = strtol(directive_parameter, &int_end, base);
					sprintf((memory_map[*address]), "%.8X", value);
			} else {
				if(strlen(directive_parameter) != 12) {
					printf("ERROR on line %d\n", line_counter);
					printf("Valor hexadecimal invalido!\n");
					return false;
				}
					strcpy((memory_map[*address]), directive_parameter);
			}
		}
		be_printed[*address] = true;
	}

	(*address)++;
	return true;

}

bool apply_align(int *address, char *directive_parameter, int line_counter) {
	char *string_start = directive_parameter;
	if(find_base(string_start) == 10) {
		int value = strtol(directive_parameter, &string_start, 10);
		while((*address) % value != 0) {
			(*address)++;
		}
		return true;
	} else {
		printf("ERROR on line %d\n", line_counter);
		printf("Valor não é hexadecimal!\n");
		return false;
	}
}

bool apply_wfill(int *address, char *directive_parameter, char **memory_map, char **string_end
								, Label_list label_head_node, Alias_list alias_head_node, bool *be_printed, int line_counter) {
	//Avalia o tamanho do endereco
	if((*address > 1024) || (*address < 0)) {
		printf("ERROR on line %d\n", line_counter);
		printf("Endereco invalido!\n");
		return false;
	}
	//Encontra a base do segundo parametro
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
		printf("ERROR on line %d\n", line_counter);
		printf("Falta o segundo parametro!\n");
		return false;
	}
	//Armazena os valores entre o string_end e string_start em parameter_2.
	char *parameter_2 = malloc(MAX_SIZE + 1 * sizeof(char));
	int i = 0;
	for(char *probe = string_start ; probe != *string_end; probe++, i++) {
		parameter_2[i] = *probe;
	}
	parameter_2[i] = '\0';

	int base_2 = find_base(parameter_2);

	//Verifica o primeiro parametro.
	int base_1 = find_base(directive_parameter);
	if( base_1 != 10) {
		printf("ERROR on line %d\n", line_counter);
		printf("Primeiro parametro não é um valor decimal valido!\n");
		return false;
	}
	int repetitions = strtol(directive_parameter, &string_start, base_1);
	if(((*address) + repetitions) > 1024) {
		printf("ERROR on line %d\n", line_counter);
		printf("Repeticoes ultrapassam limite do mapa de memoria!\n");
		return false; //O numero de repeticoes ira ultrapassar o limite das palavras de memoria.
	}
	if(be_printed) {
		if(base_2 == -1) {
			//Verifica nos simbolos e rotulos
			Label *token = find_label(label_head_node, directive_parameter);
			Alias *symbol = find_alias(alias_head_node, directive_parameter);
			if(token) {
				int value = token->address;
				for(int i = 0; i < repetitions; i++) {
					sprintf((memory_map[*address]), "%010X", value);
					be_printed[*address] = true;
					(*address)++;
				}

			} else if(symbol) {
				unsigned int value = symbol->value;
				for(int i = 0; i < repetitions; i++) {
					sprintf((memory_map[*address]), "%010X", value);
					be_printed[*address] = true;
					(*address)++;
				}
			} else {
				printf("ERROR on line %d\n", line_counter);
				printf("Segundo parametro invalido!\n");
				return false; //O parametro nao eh um nem um numero nem um simbolo nem um rotulo.
			}
			printf("\n\n1\n\n");
		} else if (base_2 == 10) {
			long int value = strtol(parameter_2, &string_start, 10);
			if(value < 0) {
				for(int i = 0; i < repetitions; i++) {
					memory_map[*address][0] = 'F';
					memory_map[*address][1] = 'F';
					sprintf((memory_map[*address]), "%010X", (unsigned int)value);
					be_printed[*address] = true;
					(*address)++;
				}
			} else {
				for(int i = 0; i < repetitions; i++) {
					memory_map[*address][0] = '0';
					memory_map[*address][1] = '0';
					sprintf((memory_map[*address]), "%010X", (unsigned int)value);
					be_printed[*address] = true;
					(*address)++;
				}
			}
		} else if (base_2 == 16){
			if(strlen(parameter_2) != 12) {
				printf("ERROR on line %d\n", line_counter);
				printf("Valor hexadecimal invalido!\n");
				return false;
			}
			long int value = strtol(parameter_2, &string_start, 16);
			if(value < 0) {
				for(int i = 0; i < repetitions; i++) {
					memory_map[*address][0] = 'F';
					memory_map[*address][1] = 'F';
					sprintf((memory_map[*address]), "%010X", (unsigned int)value);
					be_printed[*address] = true;
					(*address)++;
				}
			} else {
				for(int i = 0; i < repetitions; i++) {
					memory_map[*address][0] = '0';
					memory_map[*address][1] = '0';
					sprintf((memory_map[*address]), "%010X", (unsigned int)value);
					(*address)++;
				}
			}
		}
	} else {
		for(int i = 0; i < repetitions; i++) {
			(*address)++;
		}
	}

	return true;
}

bool apply_set(Alias_list head_node, char *directive_parameter
								, char **string_end, Label_list label_head_node, int line_counter) {
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
		printf("ERROR on line %d\n", line_counter);
		printf("Não ha segundo parametro!\n");
		return false;
	}

	//Armazena os valores entre o string_end e string_start em parameter_2.
	char *parameter_2 = malloc(MAX_SIZE + 1 * sizeof(char));
	int i = 0;
	for(char *probe = string_start ; probe != *string_end ; probe++, i++) {
		parameter_2[i] = *probe;
	}
	parameter_2[i] = '\0';

	//Avalia o primeiro parametro, que equivale ao simbolo.
	for(int i = 0; i < strlen(directive_parameter); i++) {
		if(!isalnum(directive_parameter[i]) && (directive_parameter[i] != '_')) {
			printf("ERROR on line %d\n", line_counter);
			printf("asdddasdasd\n");
			printf("O simbolo possui caractere invalido!\n");
			return false;
		}
	}
	if(head_node && label_head_node) {
		//Verifica se ha um simbolo com mesmo nome na lista.
		for(Alias *probe = head_node; probe ; probe=probe->next) {
			if(strcmp(probe->name, directive_parameter) == 0) {
				printf("ERROR on line %d\n", line_counter);
				printf("Ja existe simbolo com mesmo nome!\n");
				return false;
			}
		}
		//Verifica se ha um rotulo com mesmo nome.
		for(Label *probe = label_head_node; probe ; probe=probe->next) {
			if(strcmp(probe->name, directive_parameter) == 0) {
				printf("ERROR on line %d\n", line_counter);
				printf("Ja existe rotulo com mesmo nome!\n");
				return false;
			}
		}
	}
	//Avalia o segundo parametro, que equivale ao valor do simbolo.
	int value;
	printf("Parametro 1 =%s=, Parametro 2 =%s=\n", directive_parameter, parameter_2);
	int base = find_base(parameter_2);
	char *pointer_end;
	if(base == 10) {
		value = strtol(parameter_2, &pointer_end, 10);
	} else if(base == 16) {
		if(strlen(parameter_2) != 12) {
			printf("ERROR on line %d\n", line_counter);
			printf("Valor hexadecimal invalido!\n");
			return false;
		}
		value = strtol(parameter_2, &pointer_end, 16);
	} else {
		printf("ERROR on line %d\n", line_counter);
		printf("Valor invalido!\n");
		return false;
	}

	add_alias(directive_parameter, value, head_node);
	return true;
}
