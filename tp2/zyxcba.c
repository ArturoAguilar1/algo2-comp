#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "funciones_tp2.h"
#include "clinica.h"
#include "strutil.h"
#include "mensajes.h"
#include "paciente.h"
#include "lista.h"
#include "csv.h"
#include "turnos.h"

//PEDIR_TURNO:NOMBRE_PACIENTE,NOMBRE_ESPECIALIDAD,URGENCIA
#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"

//ATENDER_SIGUIENTE:NOMBRE_DOCTOR
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"

//INFORME:[INICIO],[FIN]
#define COMANDO_INFORME "INFORME"



void procesar_comando(clinica_t *clinica,const char* comando,char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		clinica_pedir_turno(clinica,parametros);
			// clinica_imprimir_pedir_turno(st_pedir_turno);
			//fprintf(stdout,st);
		//procesar_pedir_turno(parametros);
		//fprintf(stdout,"comando encontrado %s \n",comando);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		clinica_atender_siguiente(clinica,parametros);
		//clinica_imprimir_atender(clinica,st_cmd_atender);
		//procesar_atender(parametros);
		//fprintf(stdout,"comando encontrado %s \n",comando);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		//clinica_informe_doctores(clinica,parametros);
		//procesar_informe(parametros);
		//fprintf(stdout,"comando encontrado %s \n",comando);
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

void procesar_entrada(clinica_t *clinica) {
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
		procesar_comando(clinica,campos[0], parametros);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stdout,ENOENT_CANT_PARAMS);
		return 1;
	}
	clinica_t *clinica = clinica_crear(argv[1],argv[2]);
	if(!clinica)
		return 1;

	procesar_entrada(clinica);

	clinica_destruir(clinica);
	//liberar memoria, listas.
	return 0;
}
