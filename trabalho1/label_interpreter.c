#include "label_interpreter.h"

//Verifica se a string possui um rotulo valido.
//Retorna o final do rotulo + 1 caso possua um rotulo e retorna null caso contrario.
char* label_verifier(char *line, int line_counter) {
	bool has_label = false, label_error = false;
	char *string_start = line, *string_end = line;


	printf("------testando string: ");
	int j = 0;
	for(j = 0; (j < (MAX_SIZE-1)) && (line[j]!= ':'); j++) {
		printf("%c ",line[j]);
	}
	printf("\n");

	if(line[j]== ':') {
		string_end = line + j;
		//Apos a verificacao de atribuicao impropria de rotulos...

		//Verifica a presenca de caracteres que nao sejam alfanumericos ou underscore.
		char *verifier = string_start;
		label_error = true;
		while(verifier != string_end) {
			//Verifica caracteres minusculos
			for(char i = 'a'; i <= 'z'; i++) {
				if(*verifier == i) {
					label_error = false;
				}
			}
			//Verifica caracteres maiusculos
			for(char i = 'A'; i <= 'Z'; i++) {
				if(*verifier == i) {
					label_error = false;
				}
			}
			//Verifica underscore
			if(*verifier == '_') {
				label_error = false;
			}
			//Verifica numeros (exceto no inicio do rotulo)
			if(verifier != string_start) {
				for(char i = '0'; i <= '9'; i++) {
					if(*verifier == i) {
						label_error = false;
					}
				}
			}

		}

		//Verifica se o primeiro caractere eh um numero.
		for(int i = 0; i <= 9; i++) {
			if(*string_start == i + '0') {
				printf("----------Fired 1Rotulo improprio na linha %d!!\n", line_counter);
				label_error = true;
			}
		}

		//Verifica se logo apos os dois pontos (":") ha algum caractere.
		if((*(string_end + 1) != ' ') && (*(string_end + 1) != '\t')) {
			printf("----------Fired 2Rotulo improprio na linha %d!!\n", line_counter);
			label_error = true;
		}



		//... Pode ser definida a existencia de um rotulo.
		if(label_error == false) {
			has_label = true;
		}
	}

	if(has_label) {
		printf("----------Tem rotulo na linha %d!!\n", line_counter);
	} else {
		printf("----------Sem rotulo na linha %d\n", line_counter);
	}

	if(has_label) {
		return string_end;
	} else {
		return NULL;
	}
}
