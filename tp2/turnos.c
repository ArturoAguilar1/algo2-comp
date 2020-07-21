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

void turno_aumentar(turnos_t *turno){
    turno->cant_pacientes_urgencia++;
}

turnos_t *turno_crear(cmp_func_t cmp){
	turnos_t *turno = malloc(sizeof(turnos_t));
	if(!turno)  return NULL;

	turno->cola_urgencia = cola_crear();
    if(!turno->cola_urgencia){
        free(turno);
        return NULL;
    }
    turno->heap_regulares = heap_crear(cmp);
    if(!turno->heap_regulares){
        free(turno);
        cola_destruir(turno->cola_urgencia,NULL);
        return NULL;
    }
    turno->cant_pacientes_urgencia = 0;
    
    return turno;

}

bool turnos_vacios(turnos_t *turno){
	return turno->cant_pacientes_urgencia == 0 && heap_esta_vacio(turno->heap_regulares);
}

bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,const char *urgencia){
    if(strcmp(urgencia,dicc_urgencia[0]) == 0){
        if(!cola_encolar(turno->cola_urgencia,paciente))
            return false;
        turno->cant_pacientes_urgencia++;
        *cant_pacientes = turno->cant_pacientes_urgencia + heap_cantidad(turno->heap_regulares);
        
    }
    else if(strcmp(urgencia,dicc_urgencia[1]) == 0){
        if(!heap_encolar(turno->heap_regulares,paciente))
            return false;
        *cant_pacientes = turno->cant_pacientes_urgencia + heap_cantidad(turno->heap_regulares);
    } else{
        return false;
    }
    return true;
}

char *turno_desencolar(turnos_t *turno,size_t *cant_pacientes_esperar){
    char *nombre_paciente;
    if(turno->cant_pacientes_urgencia > 0){
        paciente_t *paciente = cola_desencolar(turno->cola_urgencia);
        nombre_paciente = paciente_nombre(paciente);
        turno->cant_pacientes_urgencia--;
        *cant_pacientes_esperar = turno->cant_pacientes_urgencia + heap_cantidad(turno->heap_regulares);
    }
    else{
        paciente_t *paciente = heap_desencolar(turno->heap_regulares);
        nombre_paciente = paciente_nombre(paciente);
        *cant_pacientes_esperar = turno->cant_pacientes_urgencia + heap_cantidad(turno->heap_regulares);
    }
    return nombre_paciente;
}

void turnos_destruir(turnos_t *turno){
	heap_destruir(turno->heap_regulares,NULL);
	cola_destruir(turno->cola_urgencia,NULL);
	free(turno);
}


void turno_imprimir_cola_urgencia(turnos_t *turno){
    cola_imprimir(turno->cola_urgencia);
}

void turno_imprimir_heap_regulares(turnos_t *turno){
    heap_imprimir(turno->heap_regulares);
}

size_t turno_cant_pacientes_urgencia(turnos_t *turno){
    return turno->cant_pacientes_urgencia;
}

