#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //Obtem o nome do arquivo de entrada
    FILE *file = fopen(argv[1], "r");




    //Fecha o arquivo de entrada caso o mesmo tenha sido aberto.
    if(file) {
        while(file != EOF) {

        }
        //Le o arquivo linha por linha
        fclose(file);
    }
    return 0;
}
