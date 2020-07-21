#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct doctor doctor_t;

// Crea un expediente del doctor, indicando su nombre y especialidad.
doctor_t *doctor_crear(const char *nombre, char* especialidad);

// Destruye el expediente del doctor.
// Pre: El expediente del mismo fue creado.
// Post: Se destruyó su expediente.
void doctor_destruir(doctor_t *doc);

// Crea un expediente del doctor, indicando su nombre y especialidad.
void *doctor_parse(char** params, void *extra);

// Imprime el expediente del doctor.
// Pre: El expediente del doctor fue creado.
void doctor_imprimir(doctor_t *doc);

// Devuelve la especialidad del doctor.
// Pre: El expediente del doctor fue creado.
char *doctor_especialidad(doctor_t *doc);

// Devuelve el nombre del doctor en cuestión.
// Pre: El expediente del doctor fue creado.
const char *doctor_nombre(doctor_t *doc);

// Aumenta en uno la cantidad de pacientes que atendió el doctor.
// Pre: El expediente del doctor fue creado.
void doctor_atender(doctor_t *doc);

// Devuelve la cantidad de pacientes que atendió el doctor.
// Pre: El expediente del doctor fue creado.
size_t doctor_cantidad_pacientes_atendidos(doctor_t *doc);

#endif

