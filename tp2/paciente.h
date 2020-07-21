#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente paciente_t;

// Crea un expediente de un paciente, informando su nombre y su antiguedad en la clínica.
paciente_t *paciente_crear(const char *nombre, int ano);

// Destruye el expediente del paciente
// Pre: El expediente del mismo fue creado.
// Post: Se destruyó su expediente.
void paciente_destruir(paciente_t *p);

// Crea un expediente del paciente, informando su nombre y su antiguedad en la clínica
void *paciente_parse(char** params, void *extra);

// Imprime el expediente del paciente.
// Pre: El expediente del paciente fue creado.
void paciente_imprimir(paciente_t *pac);

// Devuelve el año en el que se inscribió el paciente.
// Pre: El expediente del paciente fue creado.
int paciente_ano_inscripcion(paciente_t *paciente);

// Devuelve el nombre del paciente en cuestión.
// Pre: El expediente del paciente fue creado.
char *paciente_nombre(paciente_t *pac);

#endif

