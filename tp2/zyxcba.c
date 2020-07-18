#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "funciones_tp2.h"
#include "strutil.h"
#include "mensajes.h"
#include "lista.h"
#include "doctor.h"
#include "paciente.h"
#include "csv.h"

//PEDIR_TURNO:NOMBRE_PACIENTE,NOMBRE_ESPECIALIDAD,URGENCIA
#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"

//ATENDER_SIGUIENTE:NOMBRE_DOCTOR
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"

//INFORME:[INICIO],[FIN]
#define COMANDO_INFORME "INFORME"

typedef enum{
	URGENTE = 1,
	REGULAR = 0
}urgencia_t;

void procesar_comando(const char* comando,char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		//procesar_pedir_turno(parametros);
		fprintf(stdout,"comando encontrado %s \n",comando);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		//procesar_atender(parametros);
	fprintf(stdout,"comando encontrado %s \n",comando);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		//procesar_informe(parametros);
	fprintf(stdout,"comando encontrado %s \n",comando);
	} else {
		fprintf(stdout,ENOENT_CMD,comando);
	}
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada() {
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0){
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], parametros);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}

bool imp_doctores(void *dato, void*extra){
	doctor_imprimir(dato);
	return true;
}

bool imp_pacientes(void *dato, void *extra){
	paciente_imprimir(dato);
	return true;
}

void wrraper_destruir_doc(void *dato){
	doctor_destruir(dato);
}

void wrraper_destruir_pac(void *dato){
	paciente_destruir(dato);
}

int main(int argc, char** argv){
	//Cargar archivos en memoria, en listas
	//lista_doctores, lista_pacientes
	//llamar a procesar entrada
	if(argc != 3){
		fprintf(stdout,"Error al invocar el programa\n");
		return 1;
	}
	lista_t *lista_doctores = csv_crear_estructura(argv[1],doctor_parse,NULL);
	if(!lista_doctores)	return 1;
	lista_t *lista_pacientes = csv_crear_estructura(argv[2],paciente_parse,NULL);
	if(!lista_pacientes){
		lista_destruir(lista_doctores,wrraper_destruir_doc);
		return 1;
	}

	// lista_iterar(lista_doctores,imp_doctores,NULL);
	// printf("\n\n");
	// lista_iterar(lista_pacientes,imp_pacientes,NULL);

	procesar_entrada();



	lista_destruir(lista_pacientes,wrraper_destruir_pac);
	lista_destruir(lista_doctores,wrraper_destruir_doc);
	//liberar memoria, listas.
	return 0;
}
