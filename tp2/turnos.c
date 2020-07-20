#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "paciente.h"
#include "cola.h"
#include "heap.h"
#include "mensajes.h"
#include "turnos.h"

typedef enum{
	URGENTE = 1,
	REGULAR = 0
}urgencia_t;

char *dicc_urgencia[] = {
    "URGENTE",
    "REGULAR"
};

struct turnos{
	cola_t *cola_urgencia;
	heap_t *heap_regulares;
    size_t cant_pacientes_urgencia;
};

int prioridad_pacientes(const void *a, const void *b){
	return 0;
}

turnos_t *turno_crear(){
	turnos_t *turno = malloc(sizeof(turnos_t));
	if(!turno){
        printf("No lo creé \n");
        return NULL;
    }

	turno->cant_pacientes_urgencia = 0;
	turno->cola_urgencia = cola_crear();
	if(turno->cola_urgencia){
        printf("Creé la urgencia \n");
    }
    turno->heap_regulares = heap_crear(prioridad_pacientes);
    if(turno->heap_regulares){
        printf("Creé el heap \n");
    }
    
    return turno;

}

bool turnos_vacios(turnos_t *turno){
	return turno->cant_pacientes_urgencia == 0 && heap_esta_vacio(turno->heap_regulares);
}

bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,const char *urgencia){
    printf("::::::%s \n",urgencia);
        //ENCOLAR urgencia
    if(!cola_encolar(turno->cola_urgencia,paciente)){
        return false;
    turno->cant_pacientes_urgencia++;
    *cant_pacientes = turno->cant_pacientes_urgencia;
    }
    else if(strcmp(urgencia,dicc_urgencia[1]) == 0){
        printf("entré aca \n");
        //Encolar regular
    printf("tam regular %lu\n",heap_cantidad(turno->heap_regulares));
    if(!heap_encolar(turno->heap_regulares,paciente))
        return false;
    printf("tam regular %lu\n",heap_cantidad(turno->heap_regulares));
    *cant_pacientes = heap_cantidad(turno->heap_regulares);
    } else{
        printf("aca?\n");
        return false;
    }
    return true;
}

bool turno_desencolar(turnos_t *turno){
    void * aux;
    if(turno->cant_pacientes_urgencia > 0){
        cola_desencolar(turno->cola_urgencia);
        turno->cant_pacientes_urgencia--;
    }
    else{
        aux = heap_desencolar(turno->heap_regulares);
        if(!aux)
            return false;
    }
    return true;
}

void turnos_destruir(turnos_t *turno){
	heap_destruir(turno->heap_regulares,NULL);
	cola_destruir(turno->cola_urgencia,NULL);
	free(turno);
}

