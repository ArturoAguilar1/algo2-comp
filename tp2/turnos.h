#ifndef __TURNOS__H_
#define __TURNOS__H_

#include "heap.h"

typedef struct turnos turnos_t;


bool turnos_vacios(turnos_t *turno);
void turnos_destruir(turnos_t *turno);
turnos_t *turno_crear(cmp_func_t cmp);
bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,const char *urgencia);
void turno_imprimir_cola_urgencia(turnos_t *turno);
void turno_imprimir_heap_regulares(turnos_t *turno);
size_t turno_cant_pacientes_urgencia(turnos_t *turno);

char *turno_desencolar(turnos_t *turno,size_t *cant_pacientes_esperar);


void turno_aumentar(turnos_t *turno);

#endif
