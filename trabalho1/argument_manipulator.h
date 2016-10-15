#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//Verifica a string, retornando a base (caso seja uma string valida) e -1 caso contrario.
int find_base(char *string_start);

//Para futura otimizacao
//Retorna a primeira palavra de uma string.
//Ignora espacos em branco no inicio e para assim que encontrar ' ', '\n' ou '\0'.
// char *find_string(char *string_start)
