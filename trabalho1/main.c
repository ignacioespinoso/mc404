#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "*.h"

#define MAX_SIZE 4097

int main(int argc, char *argv[]) {
    //Obtem o nome do arquivo de entrada
    FILE *file = fopen(argv[1], "r");
    char line[MAX_SIZE];

    //Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
    if(file) {
        while(fgets(line, sizeof(MAX_SIZE), file)) {
            printf("%s", line);
        }
        //Le o arquivo linha por linha
        fclose(file);
    }
    return 0;
}
