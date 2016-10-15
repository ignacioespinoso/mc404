#include "structures.h"

////////////////////////////Funcoes de rotulos//////////////////////////////////
//Adiciona um novo rotulo na lista ligada.
void add_label(char *name, int address, int right, Label_list head_node) {
	Label_list verifier = head_node;
	//Percorre a lista para a insercao de um no mantendo a ordem alfabetica
	while(((strcmp(name, verifier->name) < 0) && (verifier->next != NULL))) {
		verifier = verifier->next;
	}
	//Cria um novo no.
	Label_list new_label = malloc(sizeof(Label));
	new_label->name = name;
	new_label->address = address;
	new_label->right = right;

	//Caso nao tenha percorrido ate o final da lista, adiciona o rotulo entre dois
	//nos.
	if(verifier->next != NULL) {
		//O campo 'proximo' do novo no aponta para aonde o no anterior aponta.
		new_label->next = verifier->next;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_label;

	//Caso contrario, eh adicionado no final da lista
	} else {
		new_label->next = NULL;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_label;
	}
}

//Cria uma nova lista ligada de rotulos.
Label_list new_label_list() {
	Label_list head_node = malloc(sizeof(Label));
	head_node->name = "\0";
	head_node->address = -1;
	head_node->right = 0;
	head_node->next = NULL;
	return head_node;
}

//Caso encontre um rotulo com o dado nome, retorna um ponteiro para o mesmo.
//Caso contrario, retorna NULL.
Label* find_label(Label_list head_node, char *name) {
	Label *probe = head_node->next;
	while(probe && (strcmp(probe->name, name) != 0)) {
		probe = probe->next;
	}

	if(probe && (strcmp(probe->name, name) == 0)) {
		return probe;
	} else {
		return NULL;
	}
}

//Imprime todos os rotulos existentes
void print_labels(Label_list head_node) {
	Label_list probe = head_node->next;
	printf("//////////LABELS\n");
	while(probe) {
		printf("Label name:=%s=, Address: =%d=, Right: =%d=\n", probe->name, probe->address, probe->right);
		probe = probe->next;
	}
	printf("//////////\n");
}

////////////////////////////Funcoes de simbolos//////////////////////////////////
//Adiciona um novo simbolo na lista ligada.
void add_alias(char *name, unsigned int value, Alias_list head_node) {
	Alias_list verifier = head_node;
	//Percorre a lista para a insercao de um no mantendo a ordem alfabetica
	while((strcmp(name, verifier->name) < 0) && (verifier->next != NULL)) {
		verifier = verifier->next;
	}

	//Cria um novo no.
	Alias_list new_alias = malloc(sizeof(Alias));
	new_alias->name = name;
	new_alias->value = value;
	//Caso nao tenha percorrido ate o final da lista, adiciona o simbolo entre dois
	//nos.
	if(verifier->next != NULL) {
		//O campo 'proximo' do novo no aponta para aonde o no anterior aponta.
		new_alias->next = verifier->next;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_alias;

	//Caso contrario, eh adicionado no final da lista
	} else {
		new_alias->next = NULL;
		//O campo 'proximo' do no anterior aponta para o novo no.
		verifier->next = new_alias;
	}
}

//Cria uma nova lista ligada de simbolos.
Alias_list new_alias_list() {
	Alias_list head_node = malloc(sizeof(Alias));
	head_node->name = "\0";
	head_node->value = -1;
	head_node->next = NULL;
	return head_node;
}

//Caso encontre um simbolo com o dado nome, retorna um ponteiro para o mesmo.
//Caso contrario, retorna NULL.
Alias* find_alias(Alias_list head_node, char *name) {
	Alias *probe = head_node->next;
	while(probe && (strcmp(probe->name, name) != 0)) {
		probe = probe->next;
	}

	if(probe && (strcmp(probe->name, name) == 0)) {
		return probe;
	} else {
		return NULL;
	}
}

//Imprime todos os simbolos.
void print_aliases(Alias_list head_node) {
	Alias_list probe = head_node->next;
	printf("//////////ALIASES\n");
	while(probe) {
		printf("Alias name: =%s=, Value: =%d=\n", probe->name, probe->value);
		probe = probe->next;
	}
	printf("//////////\n");
}
