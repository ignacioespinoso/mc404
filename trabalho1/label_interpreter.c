#include "label_interpreter.h"

//Verifica se a string possui um rotulo valido.
//Retorna 1 para rotulo valido, 0 para ausencia de rotulo e -1 para rotulo invalido
int label_verifier(char *line, Label_list head_node, char **string_end) {
	bool has_label = false, label_error = false;
	char *string_start = line;

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
	// Verifica se ha um rotulo com mesmo nome na lista.
	if(has_label) {
		char *label_name = malloc(MAX_SIZE * sizeof(char));
		char *probe = line;
		for(int i = 0; probe != (*string_end); probe++, i++) {
			label_name[i] = *probe;
		}


		while((head_node->next != NULL) && (strcmp(label_name, head_node->name) < 0)) {
			head_node = head_node->next;
		}

		if(strcmp(label_name, head_node->name) == 0) {
			label_error = true;
		}

		(*string_end)++;
		//Percorre os espacos apos o rotulo.
		while(((**string_end) == ' ') && ((**string_end) != '\n') && ((**string_end) != '\0')) {
			(*string_end)++;
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

//Adiciona um novo rotulo na lista ligada.
void add_label(char *name, int address, int right, Label_list head_node) {
	Label_list verifier = head_node;
	//Percorre a lista para a insercao de um no mantendo a ordem alfabetica
	while((strcmp(name, verifier->name) < 0) && (verifier->next != NULL)) {
		verifier = verifier->next;
	}
	//Caso nao tenha percorrido ate o final da lista, adiciona o rotulo entre dois
	//nos.
	if((verifier->next != NULL) || (verifier == head_node)) {
		//Cria um novo no.
		Label_list new_label = malloc(sizeof(Label));
		new_label->name = name;
		new_label->address = address;
		new_label->right = right;
		//O campo 'proximo' do novo no aponta para aonde o no anterior aponta.
		new_label->next = verifier->next;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_label;

	//Caso contrario, eh adicionado no final da lista
	} else {
		//Cria um novo no.
		Label_list new_label = malloc(sizeof(Label));
		new_label->name = name;
		new_label->address = address;
		new_label->right = right;
		new_label->next = NULL;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_label;
	}
}

//Cria uma nova lista ligada de rotulos.
void new_label_list(Label_list *head_node) {
	(*head_node) = malloc(sizeof(Label));
	(*head_node)->name = "nameless";
	(*head_node)->address = -1;
	(*head_node)->right = 0;
	(*head_node)->next = NULL;
}

//Imprime todos os rotulos existentes
void print_labels(Label_list head_node) {
	Label_list probe = head_node->next;
	while(probe) {
		printf("Label name: %s, Address: %d, Right: %d\n", probe->name, probe->address, probe->right);
		probe = probe->next;
	}
}
