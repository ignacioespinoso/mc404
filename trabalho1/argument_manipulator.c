#include "argument_manipulator.h"

//Verifica a string, retornando a base (caso seja uma string valida) e -1 caso contrario.
int analyse_number(char *string_start) {
	//Caso seja uma base hexadecimal, verifica se a mesma eh valida.
	if((*string_start == '0') && (*(string_start+1) == 'x')) {
		while((*string_start) != ' ') {
			//Retorna -1 caso seja um numero hexadecimal invalido.
			if((!isdigit(*string_start)) && (((*string_start) < 'A') || ((*string_start) > 'F'))) {
				return -1;
			}
		}
		return 16;
	} else {
		while((*string_start) != ' ') {
			//Retorna -1 caso seja um numero decimal invalido.
			if(!isdigit(*string_start)) {
				return -1;
			}
		}
		return 10;
	}
}
