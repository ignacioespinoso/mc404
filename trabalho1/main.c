#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "label_interpreter.c"

#define MAX_SIZE 4097

int main(int argc, char *argv[]) {
    //Obtem o nome do arquivo de entrada
    FILE *file = fopen(argv[1], "r");
    char line[MAX_SIZE];

    //Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
    if(file) {
        int line_counter = 0;
        while(fgets(line, (MAX_SIZE-1) * sizeof(char), file)) {
            printf("%s", line);

            label_verifier(line, line_counter);
            //Identifica se a linha possui um rotulo
            // bool has_label = false, label_error = false;
            // char *string_start = line, *string_end = line;
            // printf("------testando string: ");
            // int j = 0;
            // for(j = 0; (j < (MAX_SIZE-1)) && (line[j]!= ':'); j++) {
            //     printf("%c ",line[j]);
            // }
            // printf("\n");
            //
            // if(line[j]== ':') {
            //     string_end = line + j;
            //     //Apos a verificacao de atribuicao impropria de rotulos...
            //     for(int i = 0; i < 9; i++) {
            //         if(*string_start == i + '0') {
            //             label_error = true;
            //         }
            //     }
            //     if((*(string_end + 1) == ' ') || (*(string_end + 1) == '\t')) {
            //         label_error = true;
            //     }
            //
            //     //... Pode ser definida a existencia de um rotulo.
            //     if(label_error == false) {
            //         has_label = true;
            //     } else {
            //         printf("----------Rotulo improprio na linha %d!!\n", line_counter);
            //     }
            // }
            // if(has_label) {
            //     printf("----------Tem rotulo na linha %d!!\n", line_counter);
            // } else {
            //     printf("----------Sem rotulo na linha %d\n", line_counter);
            // }
            //Identifica se a linha possui uma diretiva

            //Identifica se a linha possui uma instrucao

            //Identifica se a linha possui um comentario


            line_counter++;
        }
        //Le o arquivo linha por linha
        fclose(file);
    }
    return 0;
}
