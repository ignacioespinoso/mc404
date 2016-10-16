#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "label_interpreter.h"
#include "directive_interpreter.h"
#include "ias_map.h"


int main(int argc, char *argv[]) {
	//Obtem o nome do arquivo de entrada
	FILE *file = fopen(argv[1], "r");

	char line[MAX_SIZE];

	if(file) {
		int line_counter = 1, address = 0, right = -1;
		bool dont_print = false;

		//Inicializa a lista ligada de rotulos.
		Label_list label_head_node = new_label_list();

		//Inicializa a lista ligada de simbolos.
		Alias_list alias_head_node = new_alias_list();

		//Inicializa o mapa de memoria e seus enderecos a serem impressos.
		char **memory_map = new_memory_map();
		bool *be_printed = calloc(MAX_MAP_SIZE, sizeof(bool));

		//Le o arquivo linha por linha
		while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
			char *string_end = line;

////////Identifica se a linha possui um rotulo valido e cria um novo caso haja.////////////
			if(!dont_print) {
				char *label_name = malloc((MAX_LABEL_SIZE+1) * sizeof(char));
				int has_label = label_verifier(line, &string_end, label_name
																				, label_head_node, alias_head_node);

				if(has_label == 1) {
					add_label(label_name, address, right, label_head_node);
					//Percorre os espacos apos o rotulo.
					string_end++;
					while(((*string_end) == ' ') && ((*string_end) != '\n') && ((*string_end) != '\0')) {
						string_end++;
					}
				//Atua caso haja um rotulo invalido.
				} else if(has_label == -1){
					dont_print = true;
					printf("ERROR on line %d\nRotulo invalido!\n", line_counter);
				}

///////////////////Identifica se a linha possui uma diretiva////////////////////////////////////
				if(!dont_print) {
					char *directive_parameter = malloc(MAX_SIZE * sizeof(char));
					int has_directive = directive_verifier(&string_end, directive_parameter);

//////////Atua para a diretiva .org
					if(has_directive == 1) {
						printf("Possui diretiva .org na linha %d\n", line_counter);
						if(apply_org(&address, directive_parameter)) {
							right = -1;
						} else {
							dont_print = true;
						}

//////////Atua para a diretiva .word
					} else if(has_directive == 2) {
						printf("Possui diretiva .word na linha %d\n", line_counter);
						if(right == 1) {
							dont_print = true;
						} else if (!apply_word(&address, directive_parameter, memory_map
																		, label_head_node, alias_head_node, be_printed)){

							dont_print = true;
						}

//////////Atua para a diretiva .align
					} else if(has_directive == 3) {
						printf("Possui diretiva .align na linha %d\n", line_counter);
						if(apply_align(&address, directive_parameter)) {
							right = -1;
						} else {
							dont_print = true;
						}

//////////Atua para a diretiva .wfill
					} else if(has_directive == 4) {
						// apply_wfill(&address, &memory_map, directive_parameter);
						printf("Possui diretiva .wfill na linha %d\n", line_counter);


//////////Atua para a diretiva .set
					} else if(has_directive == 5) {
						printf("Possui diretiva .set na linha %d\n", line_counter);
						if(!apply_set(alias_head_node, directive_parameter, &string_end, label_head_node)) {
							dont_print = true;
						}

//////////Atua para uma diretiva invalida.
					} else if(has_directive == -1) {
						dont_print = true;
						printf("ERROR on line %d\nDiretiva invalida!\n", line_counter);
					} else {
						printf("Sem diretiva na linha %d\n", line_counter);
					}
				}
			}
//////////////////Identifica se a linha possui uma instrucao////////////////////////////


////////////////////Identifica se a linha possui um comentario////////////////////////
			// while(((*string_end) != ' ') && ((*string_end) != '\n') && ((*string_end) != '\0')) {
			// 	string_end++;
			// }
			// if(*string_end == '#') {
			// 	while(((*string_end) != '\n') && ((*string_end) != '\0')) {
			// 		string_end++;
			// 	}
			// } else if (((*string_end) != '\n') && ((*string_end) != '\0')) {
			// 	dont_print = true; //Caracteres invalidos inseridos!
			// }
			line_counter++;
		}
		print_labels(label_head_node);
		print_aliases(alias_head_node);
		if(dont_print) {
			printf("Nao vai imprimir mapa!\n");
		} else {
			printf("vai imprimir!\n");
			if(be_printed[0]) {
				printf("imprime o 1!\n");
			}
			print_map(memory_map, be_printed, MAX_MAP_SIZE);
		}
		//Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
		fclose(file);
	}
	return 0;
}
