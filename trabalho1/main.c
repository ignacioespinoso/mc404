#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "label_interpreter.h"
#include "directive_interpreter.h"
#include "instruction_interpreter.h"
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

//////////Salva os rotulos na primeira leitura do arquivo///////////////////////
//Nenhuma escrita eh feita no mapa de memoria nesta etapa.
		while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
			char *string_end = line;
			char *label_name = malloc((MAX_LABEL_SIZE+1) * sizeof(char));
			int has_label = label_verifier(line, &string_end, label_name, label_head_node);
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
			if(!dont_print) {
				char *label_name = malloc((MAX_LABEL_SIZE+1) * sizeof(char));
				int has_label = label_verifier(line, &string_end, label_name
																				, NULL);

				if(has_label == 1) {
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
					int has_directive = directive_verifier(&string_end, directive_parameter, line_counter);

//////////Atua para a diretiva .org
					if(has_directive == 1) {
						if(apply_org(&address, directive_parameter, line_counter)) {
							right = -1;
						} else {
							printf("ERROR on line %d\nDiretiva invalida!\n", line_counter);
							dont_print = true;
						}

//////////Atua para a diretiva .word
					} else if(has_directive == 2) {
						if(right == 1) {
							dont_print = true;
							printf("ERROR on line %d\nNao é possivel usar .word do lado direito!\n", line_counter);
						} else if (!apply_word(&address, directive_parameter, memory_map
																		, label_head_node, alias_head_node, NULL, line_counter)){
							printf("ERROR on line %d\nErro ao aplicar .word!\n", line_counter);
							dont_print = true;
						}

//////////Atua para a diretiva .align
					} else if(has_directive == 3) {
						if(apply_align(&address, directive_parameter, line_counter)) {
							for(int i = 8; i < 13; i++) {
								memory_map[address][i] = '0';
							}
							right = -1;
						} else {
							printf("ERROR on line %d\nErro ao aplicar .align!\n", line_counter);
							dont_print = true;
						}

//////////Atua para a diretiva .wfill
					} else if(has_directive == 4) {
						if(right == 1) {
							dont_print = true;
						} else if (!apply_wfill(&address, directive_parameter, memory_map,
							 				&string_end, label_head_node, alias_head_node, NULL, line_counter)){
							dont_print = true;
						}
						printf("o endereco final eh %d\n", address);
//////////Atua para a diretiva .set
					} else if(has_directive == 5) {
						if(!apply_set(NULL, directive_parameter, &string_end, NULL, line_counter)) {
							dont_print = true;
						}
					} else if(has_directive == -1) {
						dont_print = true;
						printf("ERROR on line %d\nDiretiva invalida!\n", line_counter);
					} else {
////////////Caso nao possua diretiva, verifica se possui uma instrucao////////////////////////
						int instruction = instruction_applier(&string_end, label_head_node
												, &address, memory_map, &right, line_counter, NULL);
						if(instruction == -1) {
							dont_print = true;
						}
					}
					//////////////////Identifica se a linha possui um comentario////////////////////////
					while(((*string_end) != ' ') && ((*string_end) != '\n') && ((*string_end) != '\0')) {
						string_end++;
					}
					if(*string_end == '#') {
						while(((*string_end) != '\n') && ((*string_end) != '\0')) {
							string_end++;
						}
					} else if (((*string_end) != '\n') && ((*string_end) != '\0')) {
						dont_print = true; //Caracteres invalidos inseridos!
					}
					line_counter++;
				}
			}
		}
		print_labels(label_head_node);
		fclose(file);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////Inicia a segunda leitura do arquivo/////////////////////////////////////////////////////////////////////////////////////////////////////////
		printf("=======================INICIANDO SEGUNDA LEITURA\n" );
		line_counter = 1;
		address = 0;
		right = -1;
		dont_print = false;
		file = fopen(argv[1], "r");

		//Le o arquivo linha por linha
		while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
			char *string_end = line;

////////Identifica se a linha possui um rotulo valido e cria um novo caso haja.////////////
			if(!dont_print) {
				char *label_name = malloc((MAX_LABEL_SIZE+1) * sizeof(char));
				int has_label = label_verifier(line, &string_end, label_name
																				, NULL);

				if(has_label == 1) {
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
					int has_directive = directive_verifier(&string_end, directive_parameter, line_counter);

//////////Atua para a diretiva .org
					if(has_directive == 1) {
						if(apply_org(&address, directive_parameter, line_counter)) {
							right = -1;
						} else {
							dont_print = true;
						}

//////////Atua para a diretiva .word
					} else if(has_directive == 2) {
						if(right == 1) {
							dont_print = true;
						} else if (!apply_word(&address, directive_parameter, memory_map
																		, label_head_node, alias_head_node, be_printed, line_counter)){
							dont_print = true;
						}

//////////Atua para a diretiva .align
					} else if(has_directive == 3) {
						if(apply_align(&address, directive_parameter, line_counter)) {
							for(int i = 8; i < 13; i++) {
								memory_map[address][i] = '0';
							}
							right = -1;
						} else {

							dont_print = true;
						}

//////////Atua para a diretiva .wfill
					} else if(has_directive == 4) {
						if(right == 1) {
							dont_print = true;
						} else if (!apply_wfill(&address, directive_parameter, memory_map,
											&string_end, label_head_node, alias_head_node, be_printed, line_counter)){

							dont_print = true;
						}

//////////Atua para a diretiva .set
					} else if(has_directive == 5) {
						if(!apply_set(alias_head_node, directive_parameter, &string_end, label_head_node, line_counter)) {
							dont_print = true;
						}
					} else if(has_directive == -1) {
						dont_print = true;
						printf("ERROR on line %d\nDiretiva invalida!\n", line_counter);
					} else {
//////////Caso nao possua diretiva, verifica se possui uma instrucao////////////////////////
						int instruction = instruction_applier(&string_end, label_head_node
																		, &address, memory_map, &right, line_counter, be_printed);
						if(instruction == -1) {
							dont_print = true;
						}
					}
				}
			}
//////////////////Identifica se a linha possui um comentario////////////////////////
			if(!dont_print) {
				while((((*string_end) == ' ') || ((*string_end) == '\t')) && ((*string_end) != '\n') && ((*string_end) != '\0')) {
					string_end++;
				}
				if(*string_end == '#') {
					while(((*string_end) != '\n') && ((*string_end) != '\0')) {
						string_end++;
					}
				} else if (((*string_end) != '\n') && ((*string_end) != '\0')) {
					printf("33string_end =%c=\n", *string_end);
					printf("ERROR on line %d\n", line_counter);
					printf("Caractere inválido!\n");
					dont_print = true; //Caracteres invalidos inseridos!
				}
			}
			line_counter++;
		}
		print_labels(label_head_node);
		print_aliases(alias_head_node);
		if(dont_print) {
			printf("Nao vai imprimir mapa!\n");
		} else {
			print_map(memory_map, be_printed, MAX_MAP_SIZE);
		}
		//Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
		fclose(file);
	}
	return 0;
}
