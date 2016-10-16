#include "structures.h"

//Verifica a string, retornando a base (caso seja uma string valida) e -1 caso contrario.
int find_base(char *string_start) {
	//Caso seja uma base hexadecimal, verifica se a mesma eh valida.
	if((*string_start == '0') && (*(string_start+1) == 'x')) {
		//Avanca os caracteres 0 e x
		string_start += 2;
		while(((*string_start) != ' ') && (*string_start) != '\0') {
			//Retorna -1 caso seja um numero hexadecimal invalido.
			if(!isxdigit(*string_start)) {
				return -1;
			}
			string_start++;
		}
		return 16;
	} else {
		if(!isdigit(*string_start) && (*string_start != '-')) {
			return -1;
		}
		string_start++;
		while(((*string_start) != ' ') && (*string_start) != '\0') {
			//Retorna -1 caso seja um numero decimal invalido.
			if(!isdigit(*string_start)) {
				return -1;
			}
			string_start++;
		}
		return 10;
	}
}

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

//Cria uma matriz com cada linha sendo um mnemonico.
char** new_mnemonic_list() {
	char **mnemonic_list = malloc(MNEMONICS_AMOUT * sizeof(char*));
	for(int i = 0; i < 17; i++) {
		mnemonic_list[i] = malloc(8 * sizeof(char));
	}

	//Atribui um mnemonico para cada linha.
	strcpy(mnemonic_list[0], "LD");
	strcpy(mnemonic_list[1], "LD-");
	strcpy(mnemonic_list[2], "LD|");
	strcpy(mnemonic_list[3], "LDmq");
	strcpy(mnemonic_list[4], "LDmq_mx");
	strcpy(mnemonic_list[5], "ST");
	strcpy(mnemonic_list[6], "JMP");
	strcpy(mnemonic_list[7], "JUMP+");
	strcpy(mnemonic_list[8], "ADD");
	strcpy(mnemonic_list[9], "ADD|");
	strcpy(mnemonic_list[10], "SUB");
	strcpy(mnemonic_list[11], "SUB|");
	strcpy(mnemonic_list[12], "MUL");
	strcpy(mnemonic_list[13], "DIV");
	strcpy(mnemonic_list[14], "LSH");
	strcpy(mnemonic_list[15], "RSH");
	strcpy(mnemonic_list[16], "STaddr");

	return mnemonic_list;
}

//Compara o mnemonico dado com a lista, retornando um valor positivo caso o mnemonico seja valido.
int find_mnemonic(char *mnemonic, char **mnemonic_list) {
	for(int i = 0; i < MNEMONICS_AMOUT; i++) {
		if(strcmp(mnemonic, mnemonic_list[i]) == 0) {
			return i;
		}
	}

	return -1;
}

char *find_op_code(int mnemonic_type, int right) {
	char *opcode = malloc(3 * sizeof(char));
	if(mnemonic_type == 0) {
		strcpy(opcode, "01");
	} else if (mnemonic_type == 1) {
		strcpy(opcode, "02");
	} else if (mnemonic_type == 2) {
		strcpy(opcode, "03");
	} else if (mnemonic_type == 3) {
		strcpy(opcode, "0A");
	} else if (mnemonic_type == 4) {
		strcpy(opcode, "09");
	} else if (mnemonic_type == 5) {
		strcpy(opcode, "21");
	} else if (mnemonic_type == 6) {
		if(right == 1) {
			strcpy(opcode, "0E");
		} else if(right == -1){
			strcpy(opcode, "0D");
		} else {
			return NULL; //Right possui valor invalido
		}
	} else if (mnemonic_type == 7) {
		if(right == 1) {
			strcpy(opcode, "10");
		} else if(right == -1){
			strcpy(opcode, "0F");
		} else {
			return NULL; //Right possui valor invalido
		}
	} else if (mnemonic_type == 8) {
		strcpy(opcode, "05");
	} else if (mnemonic_type == 9) {
		strcpy(opcode, "07");
	} else if (mnemonic_type == 10) {
		strcpy(opcode, "06");
	} else if (mnemonic_type == 11) {
		strcpy(opcode, "08");
	} else if (mnemonic_type == 12) {
		strcpy(opcode, "0B");
	} else if (mnemonic_type == 13) {
		strcpy(opcode, "0C");
	} else if (mnemonic_type == 14) {
		strcpy(opcode, "14");
	} else if (mnemonic_type == 15) {
		strcpy(opcode, "15");
	} else if (mnemonic_type == 16) {
		if(right == 1) {
			strcpy(opcode, "13");
		} else if(right == -1){
			strcpy(opcode, "12");
		} else {
			return NULL; //Right possui valor invalido
		}
		strcpy(opcode, "STaddr");
	} else if (mnemonic_type == -1){
		return NULL; //Tipo de mnemonico invalido.
	}

	return opcode;
}
