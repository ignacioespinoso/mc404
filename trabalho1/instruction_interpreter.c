#include "instruction_interpreter.h"

int instruction_applier(char **string_end, Label_list label_head_node
												, int *address, char **memory_map, int *right, int line_counter, bool *be_printed) {
	//Cria um vetor com os mnemonicos.
	char **mnemonic_list = new_mnemonic_list();
	char *string_start = *string_end;


	//Identifica se é um comentário e não um mnemônico.
	if(*string_start == '#') {
		return 0;
	}
	printf("1\n");
	//Ajusta as posicoes de escrita.
	int address_position = 1, opcode_position = 1;
	if((*right) == -1) {
		address_position = 2;
		opcode_position = 0;
	} else {
		address_position = 7;
		opcode_position = 5;
	}

	//string_start indica o inicio do mnemonico (caso exista) e string_end o final do mesmo.
	// Percorre a linha procurando pelo primeiro caractere;
	while(((*string_start == ' ') || (*string_start == '\t')) && ((*string_start) != '\n') && ((*string_start) != '\0')) {
		string_start++;
	}
	printf("3\n");
	//Caso o primeiro caractere não seja o final da string, segue percorrendo com string_end.
	if((*string_start != '\n') && (*string_start != '\0')) {
		*string_end = string_start;
		while((**string_end != ' ') && (**string_end != '\t') && ((**string_end) != '\n') && ((**string_end) != '\0')) {
			(*string_end)++;
		}
	}
	printf("COMEÇO =%c=\n", *string_start);
	printf("FIM =%c=\n", **string_end);
	int mnemonic_type = -1;
	if(((**string_end) != '\n') && ((**string_end) != '\0')) {
		//Cria uma string 'name' que armazena o nome do suposto mnemonico.
		char *name = malloc((8) * sizeof(char));

		int i = 0;
		for(char *probe = string_start ; (probe != *string_end) && (i < 7); probe++, i++) {
			name[i] = *probe;
		}
		name[i] = '\0';
		printf("NAME =%s=\n", name);
		//Verifica o mnemonico inserido e se o mesmo eh valido.
		mnemonic_type = find_mnemonic(name, mnemonic_list);
		free(name);
		if(mnemonic_type == -1) {
			printf("ERROR on line %d\n", line_counter);
			printf("Mnemonico inválido!\n");
			return -1;
		}
	}

	//Realiza o comando caso o mesmo precise do campo endereco...
	if((mnemonic_type != 3) && (mnemonic_type != 14) && (mnemonic_type != 15) && (mnemonic_type != -1)) {
		//Parameter armazena o campo endereco da instrucao.
		char *parameter = malloc(MAX_SIZE * sizeof(char));
		// Percorre a linha procurando pelo comeco do campo endereco (aspas).
		while((**string_end == ' ') && ((**string_end) != '\n') && ((**string_end) != '\0')) {
			(*string_end)++;
		}
		//Caso o primeiro caractere não seja o final da string, segue percorrendo com string_end.
		if(**string_end == '"') {
			//O comeco do parametro é o primeiro caractere após as aspas.
			(*string_end)++;
			string_start = *string_end;
			while((**string_end != ' ') && (**string_end != '\t') && ((**string_end) != '\n')
							&& ((**string_end) != '\0') && (**string_end != '"')) {
				(*string_end)++;
			}
			//Caso string_end não corresponda a aspas, o parâmetro é invalido.
			if(**string_end != '"') {
				printf("ERROR on line %d\n", line_counter);
				printf("Instrução com campo endereco inválido!\n");
				return -1;
			}

			//Copia os valores entre string_start e string_end para parameter.
			int i = 0;
			printf("STRING END EH =%c=\n", **string_end);
			for(char *probe = string_start ; (probe != *string_end); probe++, i++) {
				parameter[i] = *probe;
			}
			parameter[i] = '\0';

			//String_end agora é o primeiro caractere após as aspas.
			(*string_end)++;

			printf("A instrucao tem parametro =%s=\n", parameter);
		} else {
			printf("ERROR on line %d\n", line_counter);
			printf("Instrução sem campo endereco!\n");
			return -1;
		}

		//Avalia a string parameter.
		int base = find_base(parameter);
		char *int_end;
		//Verificação e escrita do endereço da instrução.
		//Caso o parametro nao possua uma base valida, eh feita verificacao para rotulos e simbolos.
		if(be_printed) {
			//Não sendo um numero decimal ou hexadecimal, é feita a verificação de rótulos.
			if(base == -1) {
				Label *token = find_label(label_head_node, parameter);
				if(token) {
					int value = token->address;
					if(value > 4096) {
						printf("ERROR on line %d\n", line_counter);
						printf("Valor inválido!\n");
						return -1;
					}
					char *instruction = find_op_code(mnemonic_type, token->right);
					//Escreve o campo opcode da instrução
					char *position = memory_map[*address] + opcode_position;
					strcpy(position, instruction);
					//Escreve o campo endereco da instrução
					position = memory_map[*address] + address_position;
					sprintf((memory_map[*address] + address_position), "%.3X", value);
					be_printed[*address] = true;

				} else {
					printf("ERROR on line %d\n", line_counter);
					printf("Parametro invalido!\n");
					return -1; //O parametro nao eh um nem um numero nem um rotulo.
				}
			} else {
				char *instruction = find_op_code(mnemonic_type, -1);
				//Escreve o campo opcode da instrução
				strcpy((memory_map[*address] + opcode_position), instruction);
				int value = strtol(parameter, &int_end, base);
				if(value > 4096) {
					printf("ERROR on line %d\n", line_counter);
					printf("Valor inválido!\n");
					return -1;
				}
				printf("value =%d=\n", value);
				if(base == 10) {
					//Escreve o campo endereco da instrução
					sprintf((memory_map[*address] + address_position), "%.3X", value);
				} else {
					//Valida o valor caso o mesmo seja hexadecimal.
					if(strlen(parameter) != 12) {
						printf("ERROR on line %d\n", line_counter);
						printf("Valor hexadecimal invalido!\n");
						return -1;
					}
					//Sendo um valor hexadecimal válido, o escreve no campo endereco da instrução
					sprintf((memory_map[*address] + address_position), "%.3X", value);
				}
				be_printed[*address] = true;
			}
		}
	//Não necessitando de campo endereço, apenas escreve o op_code no mapa de memoria
	//, Preenchendo os demais espaços com '0'.
	} else if (mnemonic_type != -1){
		printf("EH LSH OU RSH\n");
		char *instruction = find_op_code(mnemonic_type, -1);
		//Escreve o campo opcode da instrução
		strcpy((memory_map[*address] + opcode_position), (instruction));
		for(int i = 0; i < 3; i++) {
			memory_map[*address][address_position + i] = '0';
		}
		be_printed[*address] = true;
	} else {
		return 0;
	}
	if(mnemonic_type != -1) {
		//Em caso de escrita bem sucedida na esquerda, atualiza os valores na direita
		if(*right == -1) {
			for(int i = 5; i < 10; i++) {
				memory_map[*address][i] = '0';
			}
			//Atualiza o local de escrita.
			*right = 1;
		} else {
			*right = -1;
			(*address) += 1;
		}
		return 1;
	}

	return 0;
}
