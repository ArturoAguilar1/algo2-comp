#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "paciente.h"
#include "cola.h"
#include "heap.h"
#include "mensajes.h"
#include "turnos.h"

typedef enum{
	URGENTE = 1,
	REGULAR = 0
}urgencia_t;

struct turnos{
	cola_t *cola_urgencia;
	heap_t *heap_regulares;
    size_t cant_pacientes_urgencia;
};

int prioridad_pacientes(const void *a, const void *b){
	return 0;
}

turnos_t *turno_crear(cmp_func_t cmp){
	turnos_t *turno = malloc(sizeof(turnos_t));
	if(!turno)
		return NULL;

	turno->cant_pacientes_urgencia = 0;
	turno->cola_urgencia = cola_crear();
	turno->heap_regulares = heap_crear(cmp);

	return turno;

}

bool turnos_vacios(turnos_t *turno){
	return turno->cant_pacientes_urgencia == 0 && heap_esta_vacio(turno->heap_regulares);
}

bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,char *urgencia){
    if(!strcmp(urgencia,"URGENTE")){
        //ENCOLAR urgencia
        if(!cola_encolar(turno->cola_urgencia,paciente))
            return false;
        turno->cant_pacientes_urgencia++;
        *cant_pacientes = turno->cant_pacientes_urgencia;
    }else if(!strcmp(urgencia,"REGULAR")){
        //Encolar regular
        if(!heap_encolar(turno->heap_regulares,paciente))
            return false;
        *cant_pacientes = heap_cantidad(turno->heap_regulares);
    }else{
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

