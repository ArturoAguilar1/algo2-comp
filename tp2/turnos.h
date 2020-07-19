#ifndef __TURNOS__H_
#define __TURNOS__H_

#include "heap.h"

typedef struct turnos turnos_t;


bool turnos_vacios(turnos_t *turno);
void turnos_destruir(turnos_t *turno);
turnos_t *turno_crear();
bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,const char *urgencia);
bool turno_desencolar(turnos_t *turno);
#endif
