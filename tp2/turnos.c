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

turno_t *turno_crear(bool minimo(size_t a,size_t b)){
	turno_t *turno = malloc(sizeof(turno_t));
	
	if(!turno)
		return NULL;

	turno->cant_pacientes_urgencia = 0;
	turno->cola_urgencia = cola_crear();
	turno->heap_regulares = heap_crear(minimo);

	return turno;

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

void turno_desencolar(turnos_t *turno,char *urgencia){
	if(!strcmp(urgencia,"URGENTE")){
		if(cant_pacientes_urgencia == 0)
			printf()
		else{
			cola_desencolar(turno->cola_urgencia);
			turno->cant_pacientes_urgencia--;
		}
	}
}

