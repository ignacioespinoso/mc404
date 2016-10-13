#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "label_interpreter.h"

#define MAX_SIZE 4097

int main(int argc, char *argv[]) {
		//Obtem o nome do arquivo de entrada
		FILE *file = fopen(argv[1], "r");

		char line[MAX_SIZE];

		if(file) {
			int line_counter = 0, address = 0, right = -1;
			// bool dont_print = false;
			//Inicializa a lista ligada de rotulos.
			Label_list head_node;
			new_label_list(&head_node);

			//Le o arquivo linha por linha
			while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
				printf("%s", line);

				//Identifica se a linha possui um rotulo valido e cria um novo caso haja.
				char *string_end = line;
				int has_label = label_verifier(line, head_node, &string_end);

				if(has_label == 1) {
					//Descobre o nome do rotulo com base no resultado da verificacao
					char *label_name = malloc(MAX_SIZE * sizeof(char));
					char *probe = line;
					for(int i = 0; probe != string_end; probe++, i++) {
						label_name[i] = *probe;
					}
					add_label(label_name, address, right, head_node);
					printf("----------Tem rotulo na linha %d!!\n", line_counter);
				//Atua caso haja um rotulo invalido.
				} else if(has_label == -1){
					// dont_print = true;
					printf("ERROR on line %d\nmensagem!\n", line_counter);
				}

				//Identifica se a linha possui uma diretiva

				//Identifica se a linha possui uma instrucao

				//Identifica se a linha possui um comentario

				line_counter++;

			}
			print_labels(head_node);
			//Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
			fclose(file);
		}
	return 0;
}
