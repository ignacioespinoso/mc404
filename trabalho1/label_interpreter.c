#include "label_interpreter.h"

//Verifica se a string possui um rotulo valido.
//Retorna 1 para rotulo valido, 0 para ausencia de rotulo e -1 para rotulo invalido
int label_verifier(char *line, char **string_end, char *label_name
										, Label_list head_node){
	bool has_label = false, label_error = false;
	char *string_start = line;

	int j = 0;
	for(j = 0; (j < (MAX_SIZE-1)) && (line[j] != ':') && (line[j] != '\n'); j++);

	while(((*string_start == ' ') || (*string_start == '\t')) && (*string_start != '\n')) {
		string_start++;
	}
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
		if((*((*string_end) + 1) != ' ') && (*((*string_end) + 1) != '\n') && (*((*string_end) + 1) != '\t') && (*((*string_end) + 1) != '\n')) {
			label_error = true;
		}
	}
	// Verifica se ha um rotulo com mesmo nome na lista.
	if(has_label) {
		//Em posse dos ponteiros iniciais e finais, label_name que armazena o nome do rotulo
		char *probe = string_start;
		int i;
		for(i = 0; (probe != (*string_end)) && (i < MAX_LABEL_SIZE); probe++, i++) {
			label_name[i] = *probe;
		}
		label_name[i] = '\0';
		if(head_node) {
			Label *label_probe = head_node->next;
			while(label_probe && (strcmp(label_name, label_probe->name) < 0)) {
				label_probe = label_probe->next;
			}
			//Verifica se ha rotulo com mesmo nome ou se o nome do rotulo ultrapassou o limite
			if(label_probe && ((strcmp(label_name, label_probe->name) == 0) || (strlen(label_name) > MAX_LABEL_SIZE))) {
				label_error = true;
			}
		}
	}

	//... Pode ser definida a existencia de um rotulo.
	if(!label_error && has_label) {
		return 1;
	} else if(label_error && has_label) {
		return -1;
	} else {
		return 0;
	}
}
