#include "instruction_interpreter.h"

bool instruction_applier(char **string_end, Label_list label_head_node
												, int *address, char **memory_map, int *right, int line_counter) {
	//Cria um vetor com os mnemonicos.
	char **mnemonic_list = new_mnemonic_list();
	char *string_start = *string_end;

	//string_start indica o inicio do mnemonico (caso exista) e string_end o final do mesmo.
	// Percorre a linha procurando pelo primeiro caractere;
	while(((*string_start == ' ') || (*string_start == '\t')) && ((*string_start) != '\n') && ((*string_start) != '\0')) {
		string_start++;
	}
	//Caso o primeiro caractere não seja o final da string, segue percorrendo com string_end.
	if((*string_start != '\n') && (*string_start != '\0')) {
		*string_end = string_start;
		while((**string_end != ' ') && (**string_end != '\t') && ((**string_end) != '\n') && ((**string_end) != '\0')) {
			(*string_end)++;
		}
	}
	//Cria uma string 'name' que armazena o nome do suposto mnemonico.
	char *name = malloc((8) * sizeof(char));
	int i = 0;
	for(char *probe = string_start ; (probe != *string_end) && (i < 7); probe++, i++) {
		name[i] = *probe;
	}
	name[i] = '\0';
	//Verifica o mnemonico inserido e se o mesmo eh valido.
	int mnemonic_type = find_mnemonic(name, mnemonic_list);
	free(name);
	if(mnemonic_type == -1) {
		printf("ERROR on line %d\n", line_counter);
		printf("Mnemonico inválido!\n");
		return false;
	}

	//Realiza o comando caso o mesmo nao precise do campo endereco...
	if((mnemonic_type == 3) || (mnemonic_type == 14) ||(mnemonic_type == 15)) {
		return true;
	}
	//...Caso contrario, procura pelo campo endereco e o avalia.
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
			return false;
		}

		i = 0;
		for(char *probe = string_start ; (probe != *string_end) && (i < 7); probe++, i++) {
			parameter[i] = *probe;
		}
		parameter[i] = '\0';

		//String_end agora é o primeiro caractere após as aspas.
		(*string_end)++;

		printf("A instrucao tem parametro =%s=\n", parameter);
	} else {
		printf("ERROR on line %d\n", line_counter);
		printf("Instrução sem campo endereco!\n");
		return false;
	}

	//Avalia a string parameter.
	

	return true;
}
