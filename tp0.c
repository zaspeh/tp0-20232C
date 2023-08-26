#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NOMBRE 20
#define SEPARADOR ';'
const char TIPO_INVALIDO = 'X';

enum TIPO { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA };

struct ataque {
	char nombre[MAX_NOMBRE];
	enum TIPO tipo;
	unsigned int poder;
};

void encontrar_cualidades(char *texto, char palabra[MAX_NOMBRE],int* tope_palabra, char *letra, int *poder){

	int i = 0;
	int cantidad_separador = 0;
	int cantidad_caracteres_tipo = 0;

	while(texto[i] != '\0'){

		if(texto[i] == SEPARADOR){
			cantidad_separador++;
		}

		if(cantidad_separador == 0 && texto[i] != SEPARADOR){
			palabra[(*tope_palabra)] = texto[i];
			(*tope_palabra)++;
		} else if (cantidad_separador == 1 && texto[i] != SEPARADOR){
			(*letra) = texto[i];
			cantidad_caracteres_tipo++;
		} else if (cantidad_separador == 2 && texto[i] != SEPARADOR){
			if(isdigit(texto[i])){
				(*poder) = (*poder*10) + (texto[i]-'0');
			} else {
				
			}
		}
		
		i++;
	}

	if(cantidad_caracteres_tipo != 1){
		*letra = TIPO_INVALIDO;
	} 


}

bool validar_nombre(char palabra[MAX_NOMBRE],int tope_palabra){
	bool palabra_valida = true;

	if(strlen(palabra) > 0){
		for(int i = 0; i < tope_palabra; i++){
			if(!isalpha(palabra[i])){
				palabra_valida = false;
			}
		}
	} else {
		palabra_valida = false;
	}

	return palabra_valida;
}

bool validar_tipo(char letra){
	bool letra_valida = true;

	if(letra == TIPO_INVALIDO || !isalpha(letra)){
		letra_valida = false;
	} 


	return letra_valida;
}


bool validar_poder(int poder){
	bool poder_valido = true;

	if(poder == -1){
		poder_valido = false;
	}

	if(poder_valido){
		printf("ES VALIDO\n");
	} else {
		printf("INVALIDO CHICO\n");
	}

	return poder_valido;
}

struct ataque *parsear_ataque(char *texto, struct ataque *ataque)
{

	char palabra[MAX_NOMBRE];
	int tope_palabra = 0;
	char letra;
	int poder;


	encontrar_cualidades(texto, palabra, &tope_palabra, &letra, &poder);
	

	if(validar_nombre(palabra, tope_palabra) && validar_tipo(letra) && validar_poder(poder)){
		strcpy(ataque->nombre, palabra);
		ataque->tipo = letra;
		ataque->poder = poder;
		printf("MATIAS\n");
	} else {
		return NULL;
	}


}

int main()
{
	struct ataque un_ataque;
	int errores = 0;

	if (parsear_ataque("", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string vacío D:\n");
		errores++;
	} else
		printf("Parseo de un string vacío 👍\n");

	if (parsear_ataque("Rayo;E;", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string incorrecto D:\n");
		errores++;
	} else
		printf("Parseo de un string incorrecto 👍\n");


	if (parsear_ataque("Rayo;E;25", &un_ataque) == NULL) {
		printf("Se espera que se pueda parsear un string correcto D:\n");
		errores++;
	} else if (strcmp(un_ataque.nombre, "Rayo") == 0 &&
		 un_ataque.tipo == ELECTRICO && un_ataque.poder == 5) {
		printf("Parseo de un string correcto 👍\n");
	} else {
		printf("Se parseó el string pero los valores son incorrectos 🤔\n");
		errores++;
	}

	return errores;
}
