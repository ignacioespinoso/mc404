#ifndef IAS_MAP_DEFINED
#define IAS_MAP_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Cria um novo mapa de memoria do ias.
//Cada linha designa uma palavra de memoria
//A coluna 0 designa o endereco, as colunas 1 e 3 designam opcodes e as 2 e 4 enderecos das operacoes.
char** new_memory_map();

//Desaloca a memoria designada para o mapa de memoria
void free_memory_map(char **map);

//Imprime as palavras de memoria desejadas
void print_map (char **map, bool *be_printed, int map_size);

//Escreve um valor na memoria de acordo com os argumentos. Para right = 0
// , faz uso de todos os argumentos. Retorna 0 para endereco invalido.
// int write_data(char **map, int address, int right, int opcode1, int opcode2
// 				, int op_address1, int op_address2, bool *be_printed);
//

#endif /*IAS_MAP_DEFINED*/
