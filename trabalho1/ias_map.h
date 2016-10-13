#ifndef IAS_MAP_DEFINED
#define IAS_MAP_DEFINED

#define MAX_SIZE 4097
#define MAX_MAP_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void new_memory_map (int **map);

void print_map (int **map, int *to_be_printed);

void free_memory_map(int **map);

void print_map (int **map, bool *be_printed, int MAX_MAP_SIZE);

int write_data(int **map, int address, int right, int opcode1, int opcode2
				, int op_address1, int op_address2, bool *be_printed);


#endif /*IAS_MAP_DEFINED*/
