#include "ias_map.h"

//Cria um novo mapa de memoria do ias.
//Cada linha designa uma palavra de memoria
//A coluna 0 designa o endereco, as colunas 1 e 3 designam opcodes e as 2 e 4 enderecos das operacoes.
void new_memory_map (int **map) {
	map = malloc(1024 * sizeof(int *));
	for(int i = 0; i < 1023; i++) {
		map[i] = malloc(5 * sizeof(int));
	}
}

//Imprime as palavras de memoria desejadas
void print_map (int **map, int *to_be_printed, int length) {
	for(int i = 0;	i < length; i++) {
		//tem que implementar lista ligada dos enderecos a serem impressos
	}
}
