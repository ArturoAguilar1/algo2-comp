#ifndef __TURNOS__H_
#define __TURNOS__H_

#include "heap.h"

typedef struct turnos turnos_t;
// Informa si hay algún paciente esperando en alguna de las dos colas (urgente o regular).
// Pre: la "lista" de turnos fué creada.
// Post: devuelve true si no hay pacientes esperando, y false si todavía los hay.
bool turnos_vacios(turnos_t *turno);

// Destruye el expediente de turnos.
// Pre: El expediente del mismo fue creado.
// Post: Se destruyó su expediente.
void turnos_destruir(turnos_t *turno);

// Genera el expediente de turnos para cada especialidad, diferencia dos colas distintas para los urgentes y los regulares
turnos_t *turno_crear(cmp_func_t cmp);

// Genera un turno nuevo para un paciente, agregandolo a la cola de espera de la especialidad a la que se quiere atender, dependiendo si se trata de una urgencia o algo regular. Devuelve false si se pasa mal el nombre del paciente
// O su especialidad.
// Pre: la cola de turnos fué creada.
// Post: Se pidió exitósamente (o erróneamente (devuelve false)) un turno y se lo agrega (o no) a la cola de espera.
bool turno_encolar(turnos_t *turno, paciente_t *paciente, size_t *cant_pacientes,const char *urgencia);

// Imprime la cola para los que están en un caso de urgencia, dando información de los pacientes.
// Pre: la "lista" de turnos fué creada.
void turno_imprimir_cola_urgencia(turnos_t *turno);

// Imprime la cola para los que están en un caso de regulares, dando información de los pacientes.
// Pre: la "lista" de turnos fué creada.
void turno_imprimir_heap_regulares(turnos_t *turno);

// Devuelve la cantidad de pacientes que están esperando en la cola de urgencia.
// Pre: la "lista" de turnos fué creada.
size_t turno_cant_pacientes_urgencia(turnos_t *turno);

// Saca de la cola al paciente una vez que fué atendido, informando su nombre, considerandolo que ya fué tratado.
// Pre: la "lista" de turnos fué creada.
// Post: devuelve el nombre del paciente atendido.
char *turno_desencolar(turnos_t *turno,size_t *cant_pacientes_esperar);

// Aumenta en uno la cantidad de pacientes en la cola de espera de los casos urgentes.
// Pre: la "lista" de turnos fué creada.
void turno_aumentar(turnos_t *turno);

#endif
