#include "label_interpreter.h"

//Verifica se a string possui um rotulo valido.
//Retorna o final do rotulo + 1 caso possua um rotulo e retorna null caso contrario.
char* label_verifier(char *line, int line_counter) {
	bool has_label = false, label_error = false;
	char *string_start = line, *string_end = line;

	int j = 0;
	for(j = 0; (j < (MAX_SIZE-1)) && (line[j]!= ':'); j++);

	//Apos a verificacao de atribuicao impropria de rotulos...
	if(line[j]== ':') {
		string_end = line + j;
		has_label = true;

		//Caso algum caractere nao seja alfanumerico ou underscore, ha erro da label.
		char *verifier = string_start;
		while(verifier != string_end) {
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
		if((*(string_end + 1) != ' ') && (*(string_end + 1) != '\t') && (*(string_end + 1) != '\n')) {
			label_error = true;
		}
	}

	//... Pode ser definida a existencia de um rotulo.
	if(!label_error && has_label) {
		printf("----------Tem rotulo na linha %d!!\n", line_counter);
		return string_end;
	} else {
		printf("----------ERRO na linha %d!!\n", line_counter);
		return NULL;
	}
}
