#ifndef __TURNOS__H_
#define __TURNOS__H_

#include "heap.h"

typedef struct turnos turnos_t;


bool turnos_vacios(turnos_t *turno);
void turnos_destruir(turnos_t *turno);
turnos_t *turno_crear(cmp_func_t cmp);
bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,char *urgencia);
#endif
