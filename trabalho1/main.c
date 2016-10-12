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
		//Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
		if(file) {
			int line_counter = 0;
			
			//Le o arquivo linha por linha
			while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
				printf("%s", line);

				//Identifica se a linha possui um rotulo
				label_verifier(line, line_counter);
				//Identifica se a linha possui uma diretiva

				//Identifica se a linha possui uma instrucao

				//Identifica se a linha possui um comentario

				line_counter++;
			}

			fclose(file);
		}
	return 0;
}
