
#include "label_interpreter.h"

//Verifica se a string possui um rotulo valido.
//Retorna o final do rotulo + 1 caso possua um rotulo e retorna null caso contrario.
char* label_verifier(char *line, int line_counter) {
    bool has_label = false, label_error = false;
    char *string_start = line, *string_end = line;
    printf("------testando string: ");
    int j = 0;
    for(j = 0; (j < (MAX_SIZE-1)) && (line[j]!= ':'); j++) {
        printf("%c ",line[j]);
    }
    printf("\n");

    if(line[j]== ':') {
        string_end = line + j;
        //Apos a verificacao de atribuicao impropria de rotulos...
        for(int i = 0; i < 9; i++) {
            if(*string_start == i + '0') {
                printf("----------Fired 1Rotulo improprio na linha %d!!\n", line_counter);
                label_error = true;
            }
        }
        if((*(string_end + 1) != ' ') && (*(string_end + 1) != '\t')) {
            printf("----------Fired 2Rotulo improprio na linha %d!!\n", line_counter);
            label_error = true;
        }

        //... Pode ser definida a existencia de um rotulo.
        if(label_error == false) {
            has_label = true;
        }
    }
    if(has_label) {
        printf("----------Tem rotulo na linha %d!!\n", line_counter);
    } else {
        printf("----------Sem rotulo na linha %d\n", line_counter);
    }

    if(has_label) {
        return string_end;
    } else {
        return NULL;
    }
}
