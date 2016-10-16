#include "ias_map.h"

//Cria um novo mapa de memoria do ias.
//Cada linha designa uma palavra de memoria
//A coluna 0 designa o endereco, as colunas 1 e 3 designam opcodes e as 2 e 4 enderecos das operacoes.
char** new_memory_map () {
	char **map = malloc(MAX_MAP_SIZE * sizeof(char *));
	for(int i = 0; i < MAX_MAP_SIZE; i++) {
		map[i] = malloc(11 * sizeof(char));
	}
	for(int i = 0; i < MAX_MAP_SIZE; i++) {
		map[i][10] = '\0';
	}

	return map;
}

//Desaloca a memoria designada para o mapa de memoria
void free_memory_map(char **map) {
	for(int i = 0; i < MAX_MAP_SIZE; i++) {
		free(map[i]);
	}
	free(map);
}

//Imprime as palavras de memoria desejadas
void print_map (char **map, bool *be_printed, int map_size) {
	for(int i = 0;	i < MAX_MAP_SIZE; i++) {
		//Caso o endereco atual foi escrito, eh impressa a palavra de memoria.
		if(be_printed[i]) {
			printf("%.3X ", i);
			for(int j = 0; j < 10; j++) {
				printf("%c", map[i][j]);
				if((j == 1) ||(j == 4) ||(j == 6)) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}
}

void print_map_file (char **map, bool *be_printed, int map_size, FILE *file) {
	for(int i = 0;	i < MAX_MAP_SIZE; i++) {
		//Caso o endereco atual foi escrito, eh impressa a palavra de memoria.
		if(be_printed[i]) {
			fprintf(file, "%.3X ", i);
			for(int j = 0; j < 10; j++) {
				fprintf(file, "%c", map[i][j]);
				if((j == 1) ||(j == 4) ||(j == 6)) {
					fprintf(file, " ");
				}
			}
			fprintf(file, "\n");
		}
	}
}
